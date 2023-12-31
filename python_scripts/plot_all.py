import matplotlib.pyplot as plt 
import matplotlib.rcsetup
import matplotlib.colors as mcolors
import numpy as np 
import sys
import os
from io import StringIO
import glob
import scipy.ndimage as ndimage

# Make plots look nice
matplotlib.rcParams.update({'font.size': 15, 'font.family':'monospace'})
matplotlib.rcParams.update({'xtick.labelsize': 10})
matplotlib.rcParams.update({'ytick.labelsize': 10})
matplotlib.rcParams.update({'legend.fontsize': 10})
# matplotlib.rcParams.update({'Legend.markerscale': 5})

# Function to plot states for a certain number of rows
def plot_states(fname, rows_to_plot):
    header = []
    data = []
    state_names = {}  # Dictionary to map IDs to state names
    
    # The static power report has a weird header, need to extract state names from it
    with open(fname) as f:
        for line in f:
            if "time(us)" in line:
                break
            if line.strip():
                header.append(np.genfromtxt(StringIO(line), dtype='str', delimiter=',', ndmin=1))
        for line in f:
            data.append(np.genfromtxt(StringIO(line), delimiter=',', dtype='int', ndmin=1, max_rows=rows_to_plot))
    f.close()

    header = np.array(header)
    data = np.array(data)
    time = data[:,1]
    fig, ax = plt.subplots()
    fig.set_size_inches(10,7)  
    fig.set_dpi(200)

    for entry in header[1:]:
        state_id = int(entry[2])
        state_name = entry[1]
        state_names[state_id] = state_name

    ax.plot(time*1E-6, data[:,0], linewidth=1.0)

    plt.title("States")
    plt.xlabel("Time")
    plt.ylabel("State")
    plt.yticks([])  # Remove existing y-axis ticks
    plt.autoscale()
    plt.grid(visible=True, axis='both', which='both')
    fname_no_ending = fname.split('.')[0]
    plt.style.use('seaborn-v0_8-dark-palette')
    plt.savefig(fname_no_ending + ".png")
    
    # Manually set y-axis labels
    ax.set_yticks(list(state_names.keys()))
    ax.set_yticklabels(list(state_names.values()))
    
    plt.tight_layout()
    plt.savefig(fname_no_ending + "_with_labels.png")
    plt.close()




def plot_static_power(fname, rows_to_plot):
    with open(fname) as f:
        header = np.loadtxt(f, delimiter=',', dtype="str", max_rows=1, ndmin=1)
        data = np.loadtxt(f, delimiter=',', dtype='float', skiprows=1, ndmin=1, max_rows=rows_to_plot)
    f.close()
    print(data.shape)
    data = ndimage.zoom(data, 0.01)
    print("zoomed_size:" + data.shape)
    static_power = data[:,0]
    time = data[:,2]
    fig, ax = plt.subplots()
    fig.set_size_inches(10,7)  
    fig.set_dpi(200)

    ax.plot(time, static_power, linewidth=1.0)

    ax.set_title("Power consumed by system states")
    plt.grid(visible=True, axis='both', which='both')
    plt.legend(header[0:header.size - 2])
    plt.yticks(minor=True)
    ax.set_xlabel("Time [s]")
    ax.set_ylabel("Power [W]")
    #Save as csv
    fname_no_ending = fname.split('.')[0]
    ax.autoscale()
    # plt.yticks(np.arange(np.average(static_power)-8*np.average(static_power), np.average(static_power) + 8*np.average(static_power), 2*(np.average(static_power) + 8)/100))
    plt.style.use('seaborn-v0_8-dark-palette')
    plt.savefig(fname_no_ending + ".png")
    ##plt.show()
    plt.close()

def plot_dynamic_power(fname, rows_to_plot):
    with open(fname) as f:
        header = np.loadtxt(f, delimiter=',', dtype='str', max_rows=1, ndmin=1)
        data = np.loadtxt(f, delimiter=',', dtype='float', skiprows=1, ndmin=1, max_rows=rows_to_plot)
    f.close()

    fig, ax = plt.subplots()
    fig.set_size_inches(10,7)  
    fig.set_dpi(200)

    time = data[:,-1]

    for entry in range(header.size-1):
        ax.plot(time, data[:,entry], linewidth=2.0)

    ax.set_title("ESL event power")
    plt.grid(visible=True, axis='both', which='both')
    plt.legend(header)
    #plt.xticks(rotation=40)
    plt.yticks(minor=True)
    ax.set_xlabel("Time [s]")
    ax.set_ylabel("Power [W]")
    # ax.autoscale()
    fname_no_ending = fname.split('.')[0]
    ax.autoscale()
    plt.style.use('seaborn-v0_8-dark-palette')
    plt.savefig(fname_no_ending + ".png")
    # plt.show()
    plt.close()

def plot_events(fname, rows_to_plot):
    print("in event plot")
    with open(fname) as f:
        event_types = np.loadtxt(f, delimiter=',', dtype='str', max_rows=1, ndmin=1)
        data = np.loadtxt(f, delimiter=',', dtype='int', skiprows=1, ndmin=1, max_rows=rows_to_plot)
    f.close()

    data = ndimage.zoom(data, (0.1, 1))
    time = data[:,-1]
    event_count = []

    # Remove module name from event name (better looking plot)
    if event_types.size > 1:
        for index in range(event_types.size):
            event_types[index] = (event_types[index].split('.')[-1]).split(' ', 1)[-1]

    print(event_types)
    # Calculate the total occurrences of each event type
    for index in range(event_types.size - 1):
        event_count.append(sum(data[..., index]))

    total_events = sum(event_count)

    # Calculate the percentage of each event type
    event_percentages = [count / total_events * 100 for count in event_count]
    print("Create a pie chart")
    # Create a pie chart
    plt.style.use('seaborn-v0_8-dark-palette')
    fig1, ax1 = plt.subplots()
    fig1.set_size_inches(10, 7)
    fig1.set_dpi(200)
    ax1.pie(event_percentages, labels=event_types[0:event_types.size-1], autopct='%1.1f%%', startangle=140)
    ax1.axis('equal')  # Equal aspect ratio ensures the pie chart is circular.
    plt.tight_layout()
    fname_no_ending = fname.split('.')[0]
    plt.savefig(fname_no_ending + "_pie.png")
    plt.close()

    fig2, ax2 = plt.subplots()
    fig2.set_size_inches(10, 5)
    fig2.set_dpi(200)
    for index in range(event_types.size - 1):
        ax2.plot(time * 1E-6, data[..., index], linewidth=1.0)
    plt.title("ESL event counts")
    ax2.set_yticklabels([])
    plt.xlabel("Time")
    plt.ylabel("Number of events")
    plt.grid(visible=True, axis='both', which='both')
    plt.legend(event_types[0:event_types.size - 1])
    plt.grid(visible=True, axis='both', which='both')
    plt.autoscale()
    plt.savefig(fname_no_ending + ".png")
    plt.close()


print("Command-line arguments:", sys.argv)

if sys.argv[2] == 'None':
    rows_to_plot = None
else:
    rows_to_plot = int(sys.argv[2])

for file in glob.iglob(os.path.join('**', '*.csv'), recursive=True):
    try:
        fname = os.fsdecode(file)
        print(fname)
        if "event_power_log" in fname:
            plot_dynamic_power(fname, rows_to_plot)
        elif "eventlog" in fname:
            plot_events(fname, rows_to_plot)
        elif "statelog" in fname:
            plot_states(fname, rows_to_plot)
        elif "static_power_log" in fname:
            plot_static_power(fname, rows_to_plot)
        elif "normalized" in fname:
                with open(fname) as f:
                    data = np.loadtxt(f, delimiter=',', dtype='float', ndmin=1, max_rows=rows_to_plot)
                f.close()

                fig, ax = plt.subplots()
                fig.set_size_inches(10,7)  
                fig.set_dpi(200)

                time = data[:,-1]

                ax.plot(time, data[:,0], linewidth=2.0)
                ax.set_title("ESL power consumption")
                plt.grid(visible=True, axis='both', which='both')
                plt.legend(["total power"])
                #plt.xticks(rotation=40)
                plt.yticks(minor=True)
                ax.set_xlabel("Time [s]")
                ax.set_ylabel("Power [W]")
                # ax.autoscale()
                fname_no_ending = fname.split('.')[0]
                ax.autoscale()
                plt.style.use('seaborn-v0_8-dark-palette')
                plt.savefig(fname_no_ending + ".png")
                plt.show()
                plt.close()
        else:
            print("Log not recognized:\n " + fname)
    except Exception as e:
        print(e)