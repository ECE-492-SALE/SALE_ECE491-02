import network
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
        sleep(0.5)
        pico_led.off()
        sleep(0.5)
    # print(wlan.ifconfig())
    ip = wlan.ifconfig()[0]
    print(f'Connected to {ssid} on {ip} after {count} seconds')
    pico_led.on()
    return ip


ip_local = connect()

import socket
addr_local = (ip_local, 8060)
addr_roku  = socket.getaddrinfo('139.147.192.3', 8060)[0][-1]

socket_receive = socket.socket()
socket_receive.bind(addr_local)
socket_receive.listen(4)

print('listening on', addr_local)

while True:
    cl, addr = socket_receive.accept()
    print('client connected from', addr)
    
    socket_roku = socket.socket()
    socket_roku.connect(addr_roku)
    
    # forward request
    request_data = cl.recv(4096)
    data_sent = socket_roku.sendall(request_data)
    print(f"forwarded {data_sent} bytes")
    
    # read all the response data; will not return until roku closes connection
    response_data = socket_roku.read()
    cl.sendall(response_data)
    
    cl.close()
    

