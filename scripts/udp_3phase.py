import socket
import numpy as np
from plot_func import live_plotter

LOCAL_IP = ""
REMOTE_IP = "192.168.42.11"
PORT = 21050
MESSAGE = np.int32(5).tobytes()

# Print remote server information
print("UDP target IP: %s" % REMOTE_IP)
print("UDP target port: %s" % PORT)
print("message: %s" % MESSAGE)

# Create socket for remote connection
remotesock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

# Send start signal to UDP gate to start generation
remotesock.sendto(MESSAGE, (REMOTE_IP, PORT))

# Create socket for local connection
localsock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

# Bind to local socket to listen in on incoming UDP communication
localsock.bind((LOCAL_IP, PORT))

# Print local server information
print("UDP host IP: %s" % LOCAL_IP)
print("UDP host port: %s" % PORT)

# Initialize arrays with random noisy 3 phase data
size = 100
x_vec = np.linspace(-10,0,size)
y_vec = np.zeros((3,size))
random_noise = np.random.uniform(low=-0.1, high=0.1, size=y_vec.shape)
y_vec[0,:] = 120*(np.sin(x_vec) + random_noise[0,:])
y_vec[1,:] = 120*(np.sin(x_vec + 2*np.pi/3) + random_noise[1,:])
y_vec[2,:] = 120*(np.sin(x_vec + 4*np.pi/3) + random_noise[2,:])
lines = []

while True:
    data, addr = localsock.recvfrom(1024) # buffer size is 1024 bytes
    phase_data = np.frombuffer(data, dtype=np.float32)
    
    # Debug prints
    # print(f"received message: {phase_data}")
    # print(f"received message: {addr}")
    
    y_vec[:,-1] = phase_data
    lines = live_plotter(x_vec,y_vec,lines)
    y_vec[:,:-1] = y_vec[:,1:]
    y_vec[:,-1] = 0
