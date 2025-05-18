// Adapted from:
// https://github.com/daniloc/PicoW_HomeAssistant_Starter/tree/main/src

#include "HAIntegration.h"
#include "Credentials.h"

#include <ArduinoHA.h>
#include <WiFi.h>

//Adapted via:
//  https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/nano33iot/nano33iot.ino

#define LED_PIN     LED_BUILTIN
#define DIRECTION          22 //Physical is 27 and 29
#define POWER              21

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);
// HASwitch is an example of a HA device-type. You may need to initialize an instance of a different class for your device.
// See .pio\libdeps\pico\home-assistant-integration\src\device-types
HASwitch led("windowLED");
//HASwitch direction("Direction");
//HAButton power("Power");

HACover cover("Cover", HACover::PositionFeature);
HANumber number("CalibratePosition", HANumber::PrecisionP1);


void HAIntegration::configure() {

    //Prepare LED:

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);    
    
    // //Prepare GPIO pins:

    pinMode(DIRECTION, OUTPUT);
    digitalWrite(DIRECTION, LOW);  

    pinMode(POWER, OUTPUT);
    digitalWrite(POWER, LOW);  

    //Set device ID as MAC address

    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    //Device metadata:
    device.setName("Pico Window");
    device.setSoftwareVersion("0.1");

    // handle switch state(s)
    //led.onCommand(switchHandler);
    //led.setName("Window LED"); // optional

    // power.onCommand(onButtonCommand);
    // power.setName("TOGGLE");
    // direction.onCommand(switchHandler);
    // direction.setName("Up/Down");

    cover.onCommand(onCoverCommand);
    cover.setName("My cover"); // optional

    number.onCommand(onNumberCommand);
    number.setName("Calibrate Position");
    number.setMin(0);
    number.setMax(100);
    number.setMode(HANumber::ModeBox);


    Serial.print("Connecting to MQTT\n");
    
    if (mqtt.begin(MQTT_BROKER, MQTT_LOGIN, MQTT_PASSWORD) == true) {
        Serial.print("Connected to MQTT broker");
    } else {
        Serial.print("Could not connect to MQTT broker");
    }
}


// void HAIntegration::switchHandler(bool state, HASwitch* sender) {
//     if (sender == &led){
//     digitalWrite(LED_PIN, (state ? HIGH : LOW));
//     } else if (sender == &direction) {
//     digitalWrite(DIRECTION, (state ? HIGH : LOW));
//     }
//     sender->setState(state);  // report state back to Home Assistant
// }

// // might need to remove this.
// void HAIntegration::onButtonCommand(HAButton* sender) {
//     if (sender == &power) {
//         digitalWrite(LED_PIN, HIGH);
//         delay(1000);
//         digitalWrite(LED_PIN, LOW);
//     } else {
//         digitalWrite(POWER, LOW);
//     }
    
// }

//Cover

void HAIntegration::onCoverCommand(HACover::CoverCommand cmd, HACover* sender) {
    // Log the received command
    const char* commandStr = "";
    HACover::CoverState newState;


    switch (cmd) {
        case HACover::CommandOpen:
            commandStr = "Open";
            newState = HACover::StateOpening;
            
            digitalWrite(DIRECTION, LOW);
            digitalWrite(POWER, HIGH);
            break;

        case HACover::CommandClose:
            commandStr = "Close";
            newState = HACover::StateClosing;
            digitalWrite(DIRECTION, HIGH);
            digitalWrite(POWER, HIGH);
            break;

        case HACover::CommandStop:
            commandStr = "Stop";
            newState = HACover::StateStopped;
            digitalWrite(POWER, LOW);

            break;

        default:
            Serial.println("Unknown command received.");
            return; // Exit without updating state
    }

    // Log the command and update HA state
    Serial.print("HA Command Received: ");
    Serial.println(commandStr);

    // Report new state back to Home Assistant
    sender->setState(newState);

    sender->setPosition(50); // CALUM: hopes this will fix the issue with stop only allowing open or close
}


void HAIntegration::onNumberCommand(HANumeric number, HANumber* sender)
{
    if (!number.isSet()) {
        // the reset command was send by Home Assistant
        
    } else {
        // you can do whatever you want with the number as follows:
        float numberFloat = number.toFloat(); 
    }

    sender->setState(number); // report the selected option back to the HA panel
}





void HAIntegration::loop() {
    mqtt.loop();
}
