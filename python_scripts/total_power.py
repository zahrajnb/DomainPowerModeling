import matplotlib.pyplot as plt
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
for file in glob.iglob(os.path.join('reports', 'pd1', '**', '*.csv'), recursive=True):
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

time = data[:, -1]
total = total_event_power + total_state_power

# ... (rest of your code)

plt.rcParams.update({'font.size': 12, 'font.family': 'monospace'})
plt.rcParams.update({'xtick.labelsize': 10})
plt.rcParams.update({'ytick.labelsize': 10})
plt.rcParams.update({'legend.fontsize': 12})

fig1, ax1 = plt.subplots()
fig1.set_size_inches(12, 6)  # Adjust the figure size as needed
fig1.set_dpi(200)
plt.xticks(rotation=40, ha='right')  # Rotate and align x-axis labels
ax1.plot(time, total_event_power, linewidth=1.0)
ax1.set_title("Power consumption")
ax1.legend(("Event power"))
ax1.set_xlabel("Time [s]")
ax1.set_ylabel("Power [W]")
ax1.autoscale()
plt.grid(visible=True, axis='both', which='both')
plt.style.use('seaborn-v0_8-dark-palette')
fig1.tight_layout()  # Adjust layout
fig1.savefig(sys.argv[1] + "_total_event_power.png")
plt.show()

fig2, ax2 = plt.subplots()
fig2.set_size_inches(12, 6)  # Adjust the figure size as needed
fig2.set_dpi(200)
plt.xticks(rotation=40, ha='right')  # Rotate and align x-axis labels
ax2.plot(time, total_state_power, linewidth=1.0)
ax2.set_title("Power consumption")
ax2.legend(("State power"))
ax2.set_xlabel("Time [s]")
ax2.set_ylabel("Power [W]")
ax2.autoscale()
plt.grid(visible=True, axis='both', which='both')
plt.style.use('seaborn-v0_8-dark-palette')
fig2.tight_layout()  # Adjust layout
fig2.savefig(sys.argv[1] + "_total_state_power.png")
plt.show()

# ... (similar adjustments for other figures)
