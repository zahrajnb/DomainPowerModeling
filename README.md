# DomainPowerModeling
SystemC domain power modeling

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Processing and Visualizing Results](#processing-and-visualizing-results)
- [Credits](#credits)
- [License](#license)

## Description

This project is an approach built on top of Fused_ps, which is a full-system simulator for modeling energy-driven computers. Fused_ps accurately models the interplay between energy availability, power consumption, and execution by creating a closed feedback loop.

The power model in Fused_ps is based on recording high-level events such as memory accesses and peripheral operations, as well as capturing the states of modules (on/off) and peripheral operation modes.

In this project, we have developed a Power Domain Logger that logs power numbers for each power domain in the system. The system consists of different power domains with different active components per domain. The Power Domain Logger follows a generic approach by creating the PowerModelChannel and PowerModelBridge for each component, and performing the necessary bindings. The logger records the power consumption of each component in their respective power domains.

The Power Domain Logger leverages the power model in Fused_ps, capturing high-level events and states to calculate the instantaneous power consumption. By logging power numbers per power domain, it provides valuable insights into the power consumption of different components and their impact on the overall system's energy efficiency.

Additionally, this repository includes a simple usage example with dummy components to demonstrate the functionality of the Power Domain Logger.

The Power numbers in the power_defines.h are random numbers in the approximate power consumption range for a 60nm technology node.

## Installation

To install and set up the DomainPowerModeling project, follow the steps below:

1. Clone the repository to your local machine:
   ```shell
   git clone https://github.com/your-username/DomainPowerModeling.git

2. Navigate to the project directory:
   ```shell
   cd DomainPowerModeling

3. Update the submodules imported to the project:
   ```shell
   git submodule update --init --recursive

4. Create the Makefile using cmake in 2 steps:

   4.1. Step 1: Install the dependencies:
   
      
         mkdir build
         cd build
         cmake ./ -DINSTALL_DEPENDENCIES=ON -DINSTALL_SYSTEMC=ON
      
      

   4.2. Step 2: Clean up all the files generated by cmake and create the Makefile for the project:
   
      
         rm -rf *
         cmake ../ -DINSTALL_SYSTEMC=ON -DINSTALL_DEPENDENCIES=ON
      
      


5. Build the project:
   ```shell 
   make

6. Run the Project:
   ```shell 
   ./DomainPowerModeling

## Usage

To use the DomainPowerModeling project, follow the instructions below:

1. Include the necessary header files in your project:
   ```cpp
   #include <DomainPowerModeling/PowerDomainLogger.h>

2. Create an instance of the PowerDomainLogger class:
   ```cpp
   power_domain_logger* <logger_instance>;

3. Create a new instance for it:
   ```cpp
   power_domain_logger* <logger_instance> = new power_domain_logger("<logger_name>", "<location>", <timestep>);

4. Start the power logging process:
   ```cpp
   <logger_instance>->power_connector("<component_name>", "<component_type>", &(<component_instance>->powerModelPort), "<power_domain>");

## Processing and Visualizing Results
Once you have collected power consumption data using the Power Domain Logger, you can process and visualize the results using Python scripts:

1. Install the required libraries:
   ```shell 
   pip install pandas
   pip install matplotlib

2. Run the code total_power.py on the folder of choice to get the event power, static power, and total power plots over time for the CSVs within the folder path (you also need to change the folder location inside the python code):
   ```shell
   python3 python_scripts/total_power.py number_of_rows

3. Run domain_bar_chart.py and domain_pie_chart.py on the CSV files resulted from the run of the previous script to get the pie chart and stacked bar charts showing the power consumption contribution in total and over time (file names should be adapted based on need inside the code).

4. Run the plot_all.py on every subdirectories for each component to the statelog, eventlog, event pie chart, and event power plots. You need to pass the folder path and number of rows from the CSV files.
   ```shell
   python3 plot_all.py path_to_folder number_of_rows

5. Run plot_state.py to get the state pie charts.

6. Run module_current.py and total current.py on each folder inside the domain_currents report for each power domain to get the plots for the total and per module current consumption of each power domain.





## Credits

- **Paper 1**: "Fused: Closed-loop Performance and Energy Simulation of Embedded Systems" by [Sivert T. Sliper, William Wang, Nikos Nikoleris, Alex S. Weddell, and Geoff V. Merrett](https://eprints.soton.ac.uk/439059/1/fused_crp_final_PID6327977.pdf)
  - Fused is an open-source full-system simulator for energy-driven computers that accurately models the interplay between power supply, power consumption, and energy-driven execution, enabling hardware-software codesign and design space exploration.
- **Paper 2**: "High-Level Power Modeling for IoT" by Ingvild Overholt
  - Previous master's thesis project done in colaboration with Nordic Semiconductor

- **Git Repository 1**: Fused ([Link](https://github.com/UoS-EEC/fused.git))
  - The repository provides the necessary code and resources to use and contribute to the Fused simulator.

## License

This project is licensed under the [Apache License Version 2.0](LICENSE). See the [LICENSE](LICENSE) file for more details.


