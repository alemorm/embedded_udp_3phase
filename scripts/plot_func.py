import matplotlib.pyplot as plt
import numpy as np

# use ggplot style for more sophisticated visuals
plt.style.use('ggplot')

def live_plotter(x_vec,y1_data,y2_data,y3_data,line1,line2,line3,pause_time=0.1):
    if any([line1==[], line2==[], line3==[]]):
        # this is the call to matplotlib that allows dynamic plotting
        plt.ion()
        fig = plt.figure(figsize=(13,6))
        ax = fig.add_subplot(111)
        # create a variable for the line so we can later update it
        line1, = ax.plot(x_vec,y1_data,'r-',alpha=0.8, label='Phase A')        
        line2, = ax.plot(x_vec,y2_data,'g-',alpha=0.8, label='Phase B')        
        line3, = ax.plot(x_vec,y3_data,'b-',alpha=0.8, label='Phase C')        
        #update plot label/title
        plt.ylabel('Amplitude')
        plt.title(f'3 Phase Power')
        plt.legend(loc='upper left', fontsize=15)
        plt.ylim([-130, 130])
        plt.show()
    
    # after the figure, axis, and line are created, we only need to update the y-data
    line1.set_ydata(y1_data)
    line2.set_ydata(y2_data)
    line3.set_ydata(y3_data)
    # adjust limits if new data goes beyond bounds
    # if np.min(y1_data)<=line1.axes.get_ylim()[0] or np.max(y1_data)>=line1.axes.get_ylim()[1]:
    #     plt.ylim([np.min(y1_data)-np.std(y1_data),np.max(y1_data)+np.std(y1_data)])
   
    # if np.min(y2_data)<=line2.axes.get_ylim()[0] or np.max(y2_data)>=line2.axes.get_ylim()[1]:
    #     plt.ylim([np.min(y2_data)-np.std(y2_data),np.max(y2_data)+np.std(y2_data)])
   
    # if np.min(y3_data)<=line3.axes.get_ylim()[0] or np.max(y3_data)>=line3.axes.get_ylim()[1]:
    #     plt.ylim([np.min(y3_data)-np.std(y3_data),np.max(y3_data)+np.std(y3_data)])
    # this pauses the data so the figure/axis can catch up - the amount of pause can be altered above
    
    plt.pause(pause_time)
    
    # return line so we can update it again in the next iteration
    return line1, line2, line3