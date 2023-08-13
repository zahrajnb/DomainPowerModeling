import matplotlib.pyplot as plt 
import matplotlib.rcsetup
import matplotlib.colors as mcolors
import numpy as np 
import sys
import os
import glob

# Check if the folder path argument is provided
if len(sys.argv) < 2:
    print("Folder path not provided.")
    print("Usage: python script.py /path/to/folder")
    sys.exit(1)

total_event_power = None
total_state_power = None

# If argument is None, all rows are plotted
rows_to_plot = None
if len(sys.argv) >= 3 and sys.argv[2] != 'None':
    rows_to_plot = int(sys.argv[2])

# Search through all files in the provided folder
for file in glob.iglob(os.path.join('reports', 'pd1' , '**', '*.csv'), recursive=True):
    fname = os.fsdecode(file)
    # Add all event power
    try:
        if "event_power_log" in fname and "total" not in fname and "normalized" not in fname:
            with open(fname) as infile:
                data = np.loadtxt(infile, dtype='float', delimiter=',', skiprows=1, ndmin=2, max_rows=rows_to_plot)
            infile.close()
            if total_event_power is None:
                total_event_power = data[:, -2]
            else:
                total_event_power += data[:, -2]

        # Add all static power
        elif "static_power_log" in fname and "total" not in fname and "normalized" not in fname:
            with open(fname) as infile:
                data = np.loadtxt(infile, dtype='float', delimiter=',', skiprows=1, ndmin=2, max_rows=rows_to_plot)
            infile.close()
            if total_state_power is None:
                total_state_power = data[:, 0]
            else:
                total_state_power += data[:, 0]
    except Exception as e:
        print(e)

time = data[:,-1]
print(time)
total = total_event_power + total_state_power
print(total)

time = np.expand_dims(time, 1)
total = np.expand_dims(total, 1)  # Add a new axis to make it a 2D array
total_with_time = np.concatenate((total, time), axis=1)

np.savetxt(sys.argv[1] + "\\total_event_power.csv", total_event_power, delimiter=',')
np.savetxt(sys.argv[1] + "\\total_state_power.csv", total_state_power, delimiter=',')
np.savetxt(sys.argv[1] + "\\total_power.csv", total, delimiter=',')



matplotlib.rcParams.update({'font.size': 15, 'font.family':'monospace'})
matplotlib.rcParams.update({'xtick.labelsize': 10})
matplotlib.rcParams.update({'ytick.labelsize': 10})
matplotlib.rcParams.update({'legend.fontsize': 15})

fig1, ax1 = plt.subplots()
fig1.set_size_inches(12,6)  
fig1.set_dpi(200)
plt.xticks(rotation=40)
ax1.plot(time, total_event_power, linewidth=1.0)
ax1.set_title("Power consumption")
ax1.legend(("Event power"))
ax1.set_xlabel("Time [s]")
ax1.set_ylabel("Power [W]")
ax1.autoscale()
plt.grid(visible=True, axis='both', which='both')
plt.style.use('seaborn-v0_8-dark-palette')
fig1.savefig(sys.argv[1] + "_total_event_power.png")
fig1.show()

fig2, ax2 = plt.subplots()
fig2.set_size_inches(12,6)  
fig2.set_dpi(200)
plt.xticks(rotation=40)
ax2.plot(time, total_state_power,  linewidth=1.0)
ax2.set_title("Power consumption")
ax2.legend(("State power"))
ax2.set_xlabel("Time [s]")
ax2.set_ylabel("Power [W]")
ax2.autoscale()
plt.grid(visible=True, axis='both', which='both')
plt.style.use('seaborn-v0_8-dark-palette')
fig2.savefig(sys.argv[1] + "_total_state_power.png")
fig2.show()

fig3, ax3 = plt.subplots()
fig3.set_size_inches(12,6)  
fig3.set_dpi(200)
plt.xticks(rotation=40)
ax3.plot(time, total, linewidth=1.0)

ax3.set_title("Power consumption")
ax3.legend(("Total ESL", "Total RTL", "Min", "Max", "Average"))
ax3.set_xlabel("Time [s]")
ax3.set_ylabel("Power [W]")
fname_no_ending = fname.split('.')[0]
ax3.autoscale()
plt.grid(visible=True, axis='both', which='both')
plt.style.use('seaborn-v0_8-dark-palette')
fig3.savefig(sys.argv[1] + "_total_power.png")
fig3.show()

# ...
if time.shape[0] == total_event_power.shape[0] and time.shape[0] == total_state_power.shape[0]:
    ax1.plot(time, total_event_power, linewidth=1.0)
    ax2.plot(time, total_state_power, linewidth=1.0)
    ax3.plot(time, total, linewidth=1.0)
    # Rest of the plotting code...
else:
    print("Data shapes do not match.")

plt.close()


