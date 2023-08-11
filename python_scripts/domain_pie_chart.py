import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV files
df_pd1 = pd.read_csv('pd2_cpu_total_power.csv', header=None, names=['Power Consumption'])
df_pd2 = pd.read_csv('pd2_memory_total_power.csv', header=None, names=['Power Consumption'])
df_total_system_power = pd.read_csv('pd2total_power.csv', header=None, names=['Total Power'])

# Calculate the total power consumption for pd1 and pd2
total_pd1_power = df_pd1['Power Consumption'].sum()
total_pd2_power = df_pd2['Power Consumption'].sum()

# Get the total system power
total_system_power = df_total_system_power['Total Power'][0]

# Calculate the percentage of power consumption for pd1 and pd2
percentage_pd1 = (total_pd1_power / total_system_power) * 100
percentage_pd2 = (total_pd2_power / total_system_power) * 100

# Create the pie chart
labels = ['CPU', 'Memory']
sizes = [percentage_pd1, percentage_pd2]
colors = ['lightgreen', 'lightblue']
explode = (0.1, 0)

plt.figure(figsize=(8, 6))
plt.pie(sizes, explode=explode, labels=labels, colors=colors, autopct='%1.1f%%', shadow=True, startangle=140)
plt.title('Component Type Power Consumption Distribution in PD2')
plt.axis('equal')
plt.savefig('pd2_power_consumption_pie_chart.png')
plt.show()
