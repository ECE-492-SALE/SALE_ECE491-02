import socket
addr_local = socket.getaddrinfo('0.0.0.0', 8060)[0][-1]
addr_roku  = socket.getaddrinfo('139.147.192.3', 8060)[0][-1]

socket_receive = socket.socket()
socket_receive.bind(addr)
socket_receive.listen(4)

print('listening on', addr)

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
