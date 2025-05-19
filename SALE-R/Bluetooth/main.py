
from machine import Pin
import bluetooth
from ble_simple_peripheral import BLESimplePeripheral
import time

def main():
    # Create a Bluetooth Low Energy (BLE) object
    ble = bluetooth.BLE()
    
    # Create an instance of the BLESimplePeripheral class with the BLE object
    sp = BLESimplePeripheral(ble)

    # Configure LED as led
    led = Pin("LED", Pin.OUT)

    # Declare input pins
    pin1 = Pin(0, Pin.IN, Pin.PULL_UP)
    pin2 = Pin(1, Pin.IN, Pin.PULL_UP)
    pin3 = Pin(2, Pin.IN, Pin.PULL_UP)
    pin4 = Pin(3, Pin.IN, Pin.PULL_UP)
    pin5 = Pin(4, Pin.IN, Pin.PULL_UP)

    # Main loop
    while True:
        if sp.is_connected():

            # Check for button presses
            if pin1.value() == 0:
                msg = "LEFT"
                sp.send(msg)
                time.sleep(0.25)
            elif pin2.value() == 0:
                msg = "RIGHT"
                sp.send(msg)
                time.sleep(0.25)
            elif pin3.value() == 0:
                msg = "UP"
                sp.send(msg)
                time.sleep(0.25)
            elif pin4.value() == 0:
                msg = "DOWN"
                sp.send(msg)
                time.sleep(0.25)
            elif pin5.value() == 0:
                msg = "SELECT"
                sp.send(msg)
                time.sleep(0.25)
            else:
                msg = "NBP"
                sp.send(msg)
                time.sleep(0.25)

# Call the main function to start the program
if __name__ == "__main__":
    main()
