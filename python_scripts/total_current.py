import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('currentlog.csv')

# Group by time and sum the current for each module
grouped_df = df.groupby('time(s)').sum()

# Create the plot
plt.figure(figsize=(10, 6))
grouped_df.plot(ax=plt.gca())
plt.xlabel('Time (s)')
plt.ylabel('Total Current (A)')
plt.title('PD1 Total Current Consumption Over Time')
plt.grid(True)
plt.savefig('pd1_total_current_plot.png')
plt.show()
