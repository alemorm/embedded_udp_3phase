import socket
import numpy as np
from plot_func import live_plotter

LOCAL_IP = ""
# LOCAL_IP = "127.0.0.1"
REMOTE_IP = "192.168.42.11"
REMOTE_PORT = 21050
LOCAL_PORT = 20050
MESSAGE = np.arange(15, 18, dtype=np.float32).tobytes()

print("UDP target IP: %s" % REMOTE_IP)
print("UDP target port: %s" % REMOTE_PORT)
print("message: %s" % MESSAGE)

remotesock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

remotesock.sendto(MESSAGE, (REMOTE_IP, REMOTE_PORT))

localsock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

localsock.bind((LOCAL_IP, LOCAL_PORT))

print("UDP host IP: %s" % LOCAL_IP)
print("UDP host port: %s" % LOCAL_PORT)

size = 100
x_vec = np.linspace(0,1,size+1)[0:-1]
y_vec1 = np.sin(x_vec)
y_vec2 = np.sin(x_vec + 2*np.pi/3)
y_vec3 = np.sin(x_vec + 4*np.pi/3)
line1 = []
line2 = []
line3 = []

while True:
    print("Waiting")
    data, addr = localsock.recvfrom(1024) # buffer size is 1024 bytes
    test_data = np.frombuffer(data, dtype=np.float32)
    print(f"received message: {test_data}")
    print(f"received message: {addr}")
    
    y_vec1[-1] = test_data[0]
    y_vec2[-1] = test_data[1]
    y_vec3[-1] = test_data[2]
    line1, line2, line3 = live_plotter(x_vec,y_vec1,y_vec2,y_vec3,line1,line2,line3)
    y_vec1 = np.append(y_vec1[1:],0.0)
    y_vec2 = np.append(y_vec2[1:],0.0)
    y_vec3 = np.append(y_vec3[1:],0.0)
