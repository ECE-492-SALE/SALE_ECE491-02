// Adapted from:
// https://github.com/daniloc/PicoW_HomeAssistant_Starter/tree/main/src

#include "HAIntegration.h"
#include "Credentials.h"

#include <ArduinoHA.h>
#include <WiFi.h>
#include <AccelStepper.h>

//Adapted via:
//  https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/nano33iot/nano33iot.ino

#define LED_PIN     LED_BUILTIN

#define motorPin1  28     // IN1 on the ULN2003 driver 1
#define motorPin2  27     // IN2 on the ULN2003 driver 1
#define motorPin3  26     // IN3 on the ULN2003 driver 1
#define motorPin4  22     // IN4 on the ULN2003 driver 1
#define rev 4076
#define home 75


AccelStepper pillstepper(8, motorPin1, motorPin3, motorPin2, motorPin4);

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);
HAButton pillbox("pillbox");

void HAIntegration::configure() {

    //Prepare Pill Box:

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); 

    //pillstepper.setCurrentPosition(#);
    pillstepper.setMaxSpeed(1000.0);
    pillstepper.setAcceleration(100.0);
    pillstepper.setSpeed(200);
    pillstepper.moveTo(0);
    pillstepper.runToPosition();
        
    
    //Set device ID as MAC address

    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    //Device metadata:

    device.setName("Smart Pillbox");
    device.setSoftwareVersion("0.1");

    // handle switch state
    pillbox.onCommand(onButtonCommand);
    pillbox.setName("Smart Pillbox");

    Serial.print("Connecting to MQTT\n");
    
    if (mqtt.begin(MQTT_BROKER, MQTT_LOGIN, MQTT_PASSWORD) == true) {
        Serial.print("Connected to MQTT broker");
    } else {
        Serial.print("Could not connect to MQTT broker");
    }
}

void HAIntegration::onButtonCommand(HAButton* sender) {
    if (sender == &pillbox) {
        pillstepper.move(rev/8);
        pillstepper.enableOutputs();
        pillstepper.runToPosition();
    }
}


void HAIntegration::loop() {
    mqtt.loop();
    if(!pillstepper.isRunning()) {
        pillstepper.disableOutputs();
    }
}
