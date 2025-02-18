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

while True:
    if sp.is_connected():
            # Create a message string
            msg="This is foot remote here"
            # Send the message via BLE
            sp.send(msg)
            time.sleep(1)
            led.value(1)
            time.sleep(1)
            led.value(0)
            msg = "Hello world"
            # Send the message via BLE
            sp.send(msg)
            time.sleep(1)
            led.value(1)
            time.sleep(1)
            led.value(0)
