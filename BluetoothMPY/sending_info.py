# Import necessary modules
from machine import Pin
import bluetooth
from ble_simple_peripheral import BLESimplePeripheral
import time

# Create a Bluetooth Low Energy (BLE) object
ble = bluetooth.BLE()
# Create an instance of the BLESimplePeripheral class with the BLE object
sp = BLESimplePeripheral(ble)

# Configure LED as led
led = Pin("LED", Pin.OUT)

#Declare input pins
pin1 = Pin(0, Pin.IN, Pin.PULL_DOWN)
pin2 = Pin(1, Pin.IN, Pin.PULL_DOWN)
pin3 = Pin(2, Pin.IN, Pin.PULL_DOWN)
pin4 = Pin(3, Pin.IN, Pin.PULL_DOWN)
pin5 = Pin(4, Pin.IN, Pin.PULL_DOWN)

#Declare pull down for inactive state


while True:
    if sp.is_connected():
            # Create a message string
            msg="Kick-Button Connected"
            # Send the message via BLE
            sp.send(msg)
            time.sleep(1)
            led.value(1)
            time.sleep(1)
            led.value(0)
            msg = "Initializing transfer connection"
            # Send the message via BLE
            sp.send(msg)
            time.sleep(1)
            led.value(1)
            time.sleep(1)
            led.value(0)
            
            if pin1.value() == 1:
                msg = "UP"
                sp.send(msg)
                time.sleep(1)
            elif pin2.value() == 1:
                msg = "DOWN"
                sp.send(msg)
                time.sleep(1)
            elif pin3.value() == 1:
                msg = "LEFT"
                sp.send(msg)
                time.sleep(1)
            elif pin4.value() == 1:
                msg = "RIGHT"
                sp.send(msg)
                time.sleep(1)
            elif pin5.value() == 1:
                msg = "CENTER"
                sp.send(msg)
                time.sleep(1)
            else:
                msg = "No Button Pressed"
                sp.send(msg)
                time.sleep(1)
            
