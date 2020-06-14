import socket

UDP_IP1 = "127.0.0.1"
UDP_IP = "192.168.42.11"
# UDP_PORT = 5005
UDP_PORT = 8050
MESSAGE = b"Test python"

print("UDP target IP: %s" % UDP_IP)
print("UDP target port: %s" % UDP_PORT)
print("message: %s" % MESSAGE)

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

sock2 = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock2.bind((UDP_IP1, UDP_PORT))
while True:
    data, addr = sock2.recvfrom(1024) # buffer size is 1024 bytes
    print("received message: %f" % data[0])

# import socket

 

# msgFromClient       = "Hello UDP Server"

# bytesToSend         = str.encode(msgFromClient)

# serverAddressPort   = ("127.0.0.1", 20001)

# bufferSize          = 1024

 

# # Create a UDP socket at client side

# UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# # Send to server using created UDP socket

# UDPClientSocket.sendto(bytesToSend, serverAddressPort)

 

# msgFromServer = UDPClientSocket.recvfrom(bufferSize)

 

# msg = "Message from Server {}".format(msgFromServer[0])

# print(msg)