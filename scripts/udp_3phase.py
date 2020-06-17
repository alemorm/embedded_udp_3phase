import socket
import numpy as np
from plot_func import live_plotter

LOCAL_IP = ""
REMOTE_IP = "192.168.42.11"
PORT = 21050
MESSAGE = np.int32(5).tobytes()
BUFFER_SIZE = 64

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
array_size = 100
time_array = np.linspace(-10,0,array_size)
phase_array = np.zeros((3,array_size))
added_noise = np.random.uniform(low=-0.1, high=0.1, size=phase_array.shape)
phase_array[0,:] = 120*(np.sin(time_array) + added_noise[0,:])
phase_array[1,:] = 120*(np.sin(time_array + 2*np.pi/3) + added_noise[1,:])
phase_array[2,:] = 120*(np.sin(time_array + 4*np.pi/3) + added_noise[2,:])
lines = []

while True:
    data, addr = localsock.recvfrom(BUFFER_SIZE)
    phase_data = np.frombuffer(data, dtype=np.float32)
    
    # Debug prints
    # print(f"received message: {phase_data}")
    # print(f"received message: {addr}")
    
    phase_array[:,-1] = phase_data
    lines = live_plotter(time_array,phase_array,lines)
    phase_array[:,:-1] = phase_array[:,1:]
    phase_array[:,-1] = 0
