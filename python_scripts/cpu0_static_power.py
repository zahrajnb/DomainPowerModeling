import os
import pandas as pd
import matplotlib.pyplot as plt

# Function to read CSV files in a directory and return a DataFrame
def read_csv_files(directory):
    dfs = {}
    for root, _, files in os.walk(directory):
        for file in files:
            if "PowerChannel_static_power_log" in file and file.endswith(".csv"):
                filepath = os.path.join(root, file)
                df = pd.read_csv(filepath, skiprows=1)
                df["Time"] = df["time(s)"]
                df = df.drop(columns=["time(s)"])
                dfs[file] = df
    return dfs

# Function to calculate the total power consumption at each timestep
def calculate_total_power(dfs):
    times = set()

    for df in dfs.values():
        times.update(df["Time"])

    times = sorted(times)
    total_power = {}

    for time in times:
        total_power[time] = 0

    for df_name, df in dfs.items():
        for time in times:
            if time in df["Time"].values:
                row = df[df["Time"] == time].iloc[0]
                power = row.iloc[0]
                total_power[time] += power

    return total_power

# Function to create the bar chart showing the percentage of power consumption in cpu0
def create_cpu0_power_percentage_chart(dfs, total_power, output_folder):
    times = sorted(total_power.keys())
    cpu0_power_percentages = []

    for time in times:
        cpu0_power = dfs["cpu0PowerChannel_static_power_log.csv"].loc[dfs["cpu0PowerChannel_static_power_log.csv"]["Time"] == time].iloc[0, 0]
        cpu0_power_percentage = cpu0_power / total_power[time] * 100
        cpu0_power_percentages.append(cpu0_power_percentage)

    fig, ax = plt.subplots()
    ax.bar(times, cpu0_power_percentages, color='b')
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("CPU0 Power Consumption Percentage")
    ax.set_title("Percentage of CPU0 Power Consumption")
    plt.tight_layout()

    # Create the output subfolder inside 'reports/pd1' if it does not exist
    output_subfolder = os.path.join(output_folder, "output")
    if not os.path.exists(output_subfolder):
        os.makedirs(output_subfolder)

    output_path = os.path.join(output_subfolder, "cpu0_power_percentage_chart.png")
    plt.savefig(output_path)
    plt.close()

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Folder path not provided.")
        print("Usage: python script.py /path/to/folder")
        sys.exit(1)

    directory = sys.argv[1]  # Path to the pd1 folder containing the .csv files
    output_folder = os.path.join(directory, "reports/pd1")  # Output folder where the generated plots will be saved
    dfs = read_csv_files(directory)
    total_power = calculate_total_power(dfs)
    create_cpu0_power_percentage_chart(dfs, total_power, output_folder)
