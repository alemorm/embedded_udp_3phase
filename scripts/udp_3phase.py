import socket
import click
import struct
import pathlib
import numpy as np
from liveplotter import LivePlotter
import matplotlib.pyplot as plt
import matplotlib.animation as animation

@click.command(context_settings=dict(help_option_names=['-h', '--help']))
@click.option('-l', '--localip', type=click.STRING, default='', help='Local IP')
@click.option('-r', '--remoteip', type=click.STRING, default='192.168.42.11', help='Remote IP')
@click.option('-p', '--port', type=click.INT, default=6367, help='Port for UDP socket')
@click.option('-n', '--noise', type=click.FLOAT, default=0.1, help='Local IP')
@click.option('-t', '--timestep', type=click.FLOAT, default=0.1, help='Specify the simulation time step in seconds')
@click.option('-f', '--frequency', type=click.INT, default=20, help='Specify the simulation refresh rate in milliseconds')
@click.option('-d', '--debug', is_flag=True, help='Print UDP communication information')
@click.option('-s', '--save_animation', type=click.INT, help='Save an animation at specified frames-per-second')
def main(localip, remoteip, port, noise, timestep, frequency, debug, save_animation):
    '''Main code for starting an embedded simulation of 3 phase power and graphing it real-time'''
    simoptions = struct.pack('ffff', noise, timestep, frequency, debug)
    buffersize = 16
    pathtosrc = str(pathlib.Path(__file__).parent.parent)
    print(pathtosrc)

    if debug:
        # Print debug server information
        print(f'UDP target IP: {remoteip}')
        print(f'UDP target port: {port}')
        print(f'Simulation Options: Noise={noise}, Timestep={timestep}, Frequency={frequency}, Debug= {debug}')
        print(f'UDP host IP: {localip}')
        print(f'UDP host port: {port}')

    # Create socket for remote connection
    remotesock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP

    # Send start signal to UDP gate to start generation
    remotesock.sendto(simoptions, (remoteip, port))

    # Create socket for local connection
    localsock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP

    # Bind to local socket to listen in on incoming UDP communication
    localsock.bind((localip, port))        

    # Initialize figure and axes
    plt.rcParams.update({
    "lines.color": "white",
    "patch.edgecolor": "white",
    "text.color": "white",
    "axes.facecolor": "black",
    "axes.edgecolor": "lightgray",
    "axes.labelcolor": "white",
    "xtick.color": "white",
    "ytick.color": "white",
    "grid.color": "lightgray",
    "figure.facecolor": "black",
    "figure.edgecolor": "black",
    "savefig.facecolor": "black",
    "savefig.edgecolor": "black"})
    fig, ax = plt.subplots(figsize=(14,7))
    plotter = LivePlotter(ax, localsock, buffersize, debug, size=200, noise=noise, dt=timestep, marker='.')
    
    if save_animation:
        frames = 128
        phaseanimation = animation.FuncAnimation(fig, func=plotter.updatefig, frames=frames, interval=frequency, blit=True, repeat=False)
        plt.show()
        
        filename = pathtosrc + '/img/phaseanimation.gif'
        GifWriter = animation.PillowWriter(fps=save_animation) 
        phaseanimation.save(filename, writer=GifWriter)
    else:
        frames = iter(int, 1)
        phaseanimation = animation.FuncAnimation(fig, func=plotter.updatefig, frames=frames, interval=frequency, blit=True, repeat=False)
        plt.show()

if __name__ == '__main__':
    main()
