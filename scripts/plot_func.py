import matplotlib.pyplot as plt
import numpy as np
from string import ascii_uppercase

# use ggplot style for more sophisticated visuals
plt.style.use('ggplot')

def live_plotter(x_vec,y_data,lines,pause_time=0.1):
    if lines==[]:
        # this is the call to matplotlib that allows dynamic plotting
        plt.ion()
        fig = plt.figure(figsize=(13,6))
        ax = fig.add_subplot(111)
        # create a variable for the line so we can later update it
        for letter, y_datum in zip(ascii_uppercase,y_data):
            lines.append(ax.plot(x_vec,y_datum, alpha=0.8, label=f'Phase {letter}'))
        
        #update plot label/title
        plt.ylabel('Amplitude')
        plt.title(f'3 Phase Power')
        plt.legend(loc='upper left', fontsize=15)
        plt.ylim([-130, 130])
        plt.yticks(range(-120,121,40))
        plt.show()
    
    # after the figure, axis, and line are created, we only need to update the y-data
    for line, y_datum in zip(lines,y_data):
        line[0].set_ydata(y_datum)

    # this pauses the data so the figure/axis can catch up - the amount of pause can be altered above    
    plt.pause(pause_time)
    
    # return line so we can update it again in the next iteration
    return lines