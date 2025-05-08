// Adapted from:
// https://github.com/daniloc/PicoW_HomeAssistant_Starter/tree/main/src

#include "HAIntegration.h"
#include "Credentials.h"

#include <ArduinoHA.h>
#include <WiFi.h>

//Adapted via:
//  https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/nano33iot/nano33iot.ino

#define RELAY_PIN   28

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);
HAButton door("door");

void HAIntegration::configure() {

    //Prepare Door:

    pinMode(RELAY_PIN, OUTPUT); //Prepare pin
    digitalWrite(RELAY_PIN, LOW); //Set default mode
    
    //Set device ID as MAC address

    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    //Device metadata:

    device.setName("Smart Door");
    device.setSoftwareVersion("0.1");

    // handle switch state
    door.onCommand(onButtonCommand);
    door.setName("Open"); // optional

    Serial.print("Connecting to MQTT\n");
    
    if (mqtt.begin(MQTT_BROKER, MQTT_LOGIN, MQTT_PASSWORD) == true) {
        Serial.print("Connected to MQTT broker");
    } else {
        Serial.print("Could not connect to MQTT broker");
    }
}

void HAIntegration::onButtonCommand(HAButton* sender) {
    //digitalWrite(RELAY_PIN, (!digitalRead(RELAY_PIN) ? HIGH : LOW)); //Set door state, default off if null
    digitalWrite(RELAY_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY_PIN, LOW);
}


void HAIntegration::loop() {
    mqtt.loop(); 
}
