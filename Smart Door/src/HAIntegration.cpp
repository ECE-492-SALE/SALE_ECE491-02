// Adapted from:
// https://github.com/daniloc/PicoW_HomeAssistant_Starter/tree/main/src

#include "HAIntegration.h"
#include "Credentials.h"

#include <ArduinoHA.h>
#include <WiFi.h>

//Adapted via:
//  https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/nano33iot/nano33iot.ino

#define RELAY_PIN   13

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);
HASwitch door("door");

void HAIntegration::configure() {

    //Prepare Door:

    pinMode(RELAY_PIN, OUTPUT); //Prepare pin
    digitalWrite(RELAY_PIN, LOW); //Set default mode
    
    //Set device ID as MAC address

    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    //Device metadata:

    device.setName("Pico W HA Starter");
    device.setSoftwareVersion("0.1");

    // handle switch state
    door.onCommand(switchHandler);
    door.setName("Smart Door"); // optional

    Serial.print("Connecting to MQTT\n");
    
    if (mqtt.begin(MQTT_BROKER, MQTT_LOGIN, MQTT_PASSWORD) == true) {
        Serial.print("Connected to MQTT broker");
    } else {
        Serial.print("Could not connect to MQTT broker");
    }
}

void HAIntegration::switchHandler(bool state, HASwitch* sender) {
    digitalWrite(RELAY_PIN, (state ? HIGH : LOW)); //Set door state, default off if null
    sender->setState(state);  // report state back to Home Assistant
}


void HAIntegration::loop() {
    mqtt.loop(); 
}
