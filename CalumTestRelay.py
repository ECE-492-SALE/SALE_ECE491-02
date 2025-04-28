import network
from picozero import pico_led
import time
import sys

ssid = 'pards'

def connect():
    #Connect to WLAN
    wlan = network.WLAN(network.STA_IF)
    # hopefully maybe prevent 'address in use' error
    if(wlan.isconnected()):
        wlan.disconnect()
    wlan.active(True)
    wlan.connect(ssid)
    count = 0
    # mac = ubinascii.hexlify(network.WLAN().config('mac'),':').decode()
    # print("MAC Address:", mac)
    while wlan.isconnected() == False:
        if rp2.bootsel_button() == 1:
            print('bootsel buton pressed, exiting')
            sys.exit()
        print('Waiting for connection (', count, ') ...')
        pico_led.on()
        count += 1
        time.sleep(0.5)
        pico_led.off()
        time.sleep(0.5)
    # print(wlan.ifconfig())
    ip = wlan.ifconfig()[0]
    print(f'Connected to {ssid} on {ip} after {count} seconds')
    pico_led.on()
    return ip

last_call = time.ticks_ms();
def print_time_since_last():
    global last_call
    print(time.ticks_ms()-last_call)
    last_call = time.ticks_ms()

ip_local = connect()

import socket

try:
    addr_local = (ip_local, 8060)
    addr_roku  = socket.getaddrinfo('139.147.192.3', 8060)[0][-1]

    socket_receive = socket.socket()
    socket_receive.bind(addr_local)
    socket_receive.listen(1)

    print('listening on', addr_local)


    timeout = 10

    while True:
        socket_hub, addr = socket_receive.accept()
        socket_hub.settimeout(timeout)
        print('\nclient (hub) connected from', addr)
        
        socket_roku = socket.socket()
        socket_roku.connect(addr_roku)
        socket_roku.settimeout(timeout)
        
        # forward request
        
        print_time_since_last()
        request_data = socket_hub.recv(4096)
        request_data = request_data.replace(b"139.147.192.4", b"139.147.192.3", 1)
        print(f"request data: {request_data}")
        
        data_sent = socket_roku.write(request_data)
        print_time_since_last()
        print(f"forwarded {data_sent} bytes")
        
        '''
        # read all the response data; will not return until roku closes connection - .read()
        response_data = socket_roku.read()
        print(f"response_data: {response_data}")
        socket_hub.write(response_data)'''
        
        print("response_data:")
        while True:
            socket_roku.settimeout(1)
            try:
                response_data = socket_roku.recv(256)
                
                if response_data:
                    print(response_data)
                    socket_hub.write(response_data)
                    #print_time_since_last()
                else:
                    raise Exception("done sending")
            except Exception as e:
                print_time_since_last()
                print("\ndone\n")
                break
                
        
        socket_hub.close()
        socket_roku.close()
except Exception as e:
    print(e)
    socket_receive.close()
    socket_hub.close()
    socket_roku.close()
    network.WLAN(network.STA_IF).disconnect()
    print('disconnected and shutting down')
    sys.print_exception(e)
