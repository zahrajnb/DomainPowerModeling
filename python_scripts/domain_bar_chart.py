import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV files
df_pd1 = pd.read_csv('pd2_cpu_total_power.csv', header=None, names=['Power Consumption'])
df_pd2 = pd.read_csv('pd2_memory_total_power.csv', header=None, names=['Power Consumption'])

# Calculate the total power consumption for pd1 and pd2
total_pd1_power = df_pd1['Power Consumption']
total_pd2_power = df_pd2['Power Consumption']

# Get the number of rows in the data
num_rows = len(total_pd1_power)

# Create the stacked bar chart for each row
bar_width = 0.5  # Reduced bar width
index = range(num_rows)

plt.figure(figsize=(10, 6))
plt.bar(index, total_pd1_power, bar_width, label='CPU', color='olive')
plt.bar(index, total_pd2_power, bar_width, bottom=total_pd1_power, label='Memory', color='lightblue')

plt.xlabel('Time')
plt.ylabel('Power Consumption')
plt.title('Component Type Power Consumption Distribution in PD2')
plt.xticks([])  # Remove x-axis ticks and labels
plt.legend()
plt.tight_layout()
plt.savefig('pd2_power_consumption_stacked_bar_chart.png')
plt.show()
