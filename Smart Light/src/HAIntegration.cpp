// Adapted from:
// https://github.com/daniloc/PicoW_HomeAssistant_Starter/tree/main/src

#include "HAIntegration.h"
#include "Credentials.h"

#include <ArduinoHA.h>
#include <WiFi.h>

//Adapted via:
//  https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/nano33iot/nano33iot.ino

#define LIGHT_PIN   13

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);
HASwitch light("lightREAL");

void HAIntegration::configure() {

    //Prepare Light:

    pinMode(LIGHT_PIN, OUTPUT); //Prepare pin
    digitalWrite(LIGHT_PIN, LOW); //Set default mode
    
    //Set device ID as MAC address

    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    //Device metadata:

    device.setName("Smart Light");
    device.setSoftwareVersion("0.1");

    // handle switch state
    light.onCommand(switchHandler);
    light.setName("Switch"); // optional

    Serial.print("Connecting to MQTT\n");
    
    if (mqtt.begin(MQTT_BROKER, MQTT_LOGIN, MQTT_PASSWORD) == true) {
        Serial.print("Connected to MQTT broker");
    } else {
        Serial.print("Could not connect to MQTT broker");
    }
}

void HAIntegration::switchHandler(bool state, HASwitch* sender) {
    digitalWrite(LIGHT_PIN, (state ? HIGH : LOW)); //Set light state, default off if null
    sender->setState(state);  // report state back to Home Assistant
}


void HAIntegration::loop() {
    mqtt.loop(); 
}
