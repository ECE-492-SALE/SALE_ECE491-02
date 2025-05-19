# Setting up the Smart TV

These instructions assume you already have a Roku set up on your TV.

1. Follow the steps in the [Getting started with your Raspberry Pi Pico W](https://projects.raspberrypi.org/en/projects/get-started-pico-w/0) guide to:
   - Install MicroPython onto the Pi Pico W
   - Set up the Thonny Python IDE

2. Download [`main.py`](https://github.com/ECE-492-SALE/SALE_ECE491-02/blob/main/Smart%20TV/main.py).

3. Open main.py in Thonny and edit the **Internet Credentials** section in the code to include:
   - Your Wi-Fi credentials
   - Your Roku device's IP address

4. Save the modified program to your Pico:
   - Go to `File` > `Save As` > `Raspberry Pi Pico`
   - Ensure the file name is exactly `main.py`
   - You may need to overwrite the existing `main.py` file

> **Note:** Naming the file `main.py` ensures the program starts automatically when the Pico receives power.
