import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file, skipping the header rows
with open("cpu0PowerChannel_statelog.csv") as f:
    header_lines = [next(f) for _ in range(3)]


state_names = {}
for line in header_lines[1:]:
    _, state_name, state_id = line.strip().split(',')
    state_names[int(state_id)] = state_name

# Read the CSV file, skipping the header rows and specifying the column names
data_df = pd.read_csv("cpu0PowerChannel_statelog.csv", skiprows=6, names=["State", "ID"])

# Replace the numerical labels with the state names
data_df["State"] = data_df["State"].map(state_names)

# Calculate the percentage of each state
state_percentage = data_df["State"].value_counts(normalize=True) * 100

# Generate the pie chart
plt.pie(state_percentage, labels=state_percentage.index, autopct='%1.1f%%', startangle=140)
plt.axis('equal')  # Equal aspect ratio ensures the pie chart is drawn as a circle.
plt.title("State Percentage")
plt.legend(state_percentage.index, loc="upper right")

# Save the graph as a PNG image
plt.savefig("state_percentage_pie_chart.png", dpi=200)
plt.show()
