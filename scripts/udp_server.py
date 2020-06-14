import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    print("received message: %s" % data)


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