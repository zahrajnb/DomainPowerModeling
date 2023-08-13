import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('currentlog.csv')

# Pivot the DataFrame to have modules as columns and time as index
pivot_df = df.pivot(index='time(s)', columns='moduleID', values='module_current')

# Create the plot
plt.figure(figsize=(10, 6))

# Plot each module with a different color
for module in pivot_df.columns:
    plt.plot(pivot_df.index, pivot_df[module], label=module)

plt.xlabel('Time (s)')
plt.ylabel('Current (A)')
plt.title('PD1 Current Consumption of Modules Over Time')
plt.grid(True)
plt.legend(title='Module')
plt.savefig('pd1_module_currents_plot.png')
plt.show()
