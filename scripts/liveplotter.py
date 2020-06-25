import struct
import numpy as np
import matplotlib.pyplot as plt
from string import ascii_uppercase

class LivePlotter:
    def __init__(self, ax, socketobj, buffersize, debug, size=1000, noise=0.1, dt=0.1, marker='-'):
        '''Initialize the plotting class'''
        self.ax = ax
        self.dt = dt
        self.time = 0
        self.debug = debug
        self.socket = socketobj
        self.buffersize = buffersize
        self.recvdata = np.zeros(4)
        self.newphasedata = np.zeros(3)
        self.time = np.zeros(1)
        self.tdata = np.linspace(-6*np.pi, -0.1, size)
        self.phasedata = np.zeros((3, size))
        self.noise = np.random.uniform(low=-(noise-noise/5), high=(noise-noise/5), size=self.phasedata.shape)
        self.phasedata[0,:] = 120*(np.sin(self.tdata) + self.noise[0,:])
        self.phasedata[1,:] = 120*(np.sin(self.tdata + 2*np.pi/3) + self.noise[1,:])
        self.phasedata[2,:] = 120*(np.sin(self.tdata + 4*np.pi/3) + self.noise[2,:])
        self.lines=[]
        for letter, phasedatum in zip(ascii_uppercase,self.phasedata):
            self.lines.extend(self.ax.plot(self.tdata,phasedatum, marker, alpha=0.8, label=f'Phase {letter}'))
        self.ax.set_ylabel('Amplitude', size=15)
        self.ax.set_title('3 Phase Power', pad=40, size=20)
        self.ax.set_ylim([-135, 135])
        self.ax.set_yticks(range(-120,121,40))
        self.ax.legend(bbox_to_anchor=(0,1,1,0.1), loc='lower left', mode='expand', ncol=3, fontsize=15)

    def updatefig(self, i):
        '''Update the figure with the latest data from UDP port'''
        self.UDPupdate(debug=self.debug)
        self.phasedata[:,:-1] = self.phasedata[:,1:]
        self.phasedata[:,-1] = self.newphasedata
        for num in range(len(self.lines)):
            self.lines[num].set_ydata(self.phasedata[num,:])

        return self.lines

    def UDPupdate(self, debug=False):
        '''Return the latest phase value from the UDP port'''
        data, addr = self.socket.recvfrom(self.buffersize)
        self.recvdata[:] = struct.unpack('ffff', data)
        self.newphasedata[:] = self.recvdata[:-1]
        self.time = self.recvdata[-1]

        if debug:
            # Debug prints
            if self.time <= self.dt*2:
                print(f'IP Address: {addr[0]} | Port: {addr[1]}')

            print(f'Phase data: {self.newphasedata[0]:8.3f} | {self.newphasedata[1]:8.3f} | {self.newphasedata[2]:8.3f} | Time: {self.time:7.2f}')
            

        return None
