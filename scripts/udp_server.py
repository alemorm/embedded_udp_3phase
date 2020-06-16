# import socket

# # set up the socket using local address
# socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# socket.bind(("", 9999))

# while 1:

#     # get the data sent to us
#     data, ip = socket.recvfrom(1024)

#     # display
#     print("{}: {}".format(ip, data.decode(encoding="utf-8").strip()))

#     # echo back
#     socket.sendto(data, ip)

import socket

UDP_IP = ""
UDP_PORT = 20050

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    print(f"received message: {data}")
    print(f"received message: {addr}")



# import socket

 

# localIP     = "127.0.0.1"

# localPort   = 20001

# bufferSize  = 1024

 

# msgFromServer       = "Hello UDP Client"

# bytesToSend         = str.encode(msgFromServer)

 

# # Create a datagram socket

# UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# # Bind to address and ip

# UDPServerSocket.bind((localIP, localPort))

 

# print("UDP server up and listening")

 

# # Listen for incoming datagrams

# while(True):

#     bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

#     message = bytesAddressPair[0]

#     address = bytesAddressPair[1]

#     clientMsg = "Message from Client:{}".format(message)
#     clientIP  = "Client IP Address:{}".format(address)
    
#     print(clientMsg)
#     print(clientIP)

   

#     # Sending a reply to client

#     UDPServerSocket.sendto(bytesToSend, address)