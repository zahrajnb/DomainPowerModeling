# DomainPowerModeling
SystemC domain power modeling

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)
- [License](#license)

## Description

This project is an approach built on top of Fused_ps, which is a full-system simulator for modeling energy-driven computers. Fused_ps accurately models the interplay between energy availability, power consumption, and execution by creating a closed feedback loop.

The power model in Fused_ps is based on recording high-level events such as memory accesses and peripheral operations, as well as capturing the states of modules (on/off) and peripheral operation modes.

In this project, we have developed a Power Domain Logger that logs power numbers for each power domain in the system. The system consists of different power domains with different active components per domain. The Power Domain Logger follows a generic approach by creating the PowerModelChannel and PowerModelBridge for each component, and performing the necessary bindings. The logger records the power consumption of each component in their respective power domains.

The Power Domain Logger leverages the power model in Fused_ps, capturing high-level events and states to calculate the instantaneous power consumption. By logging power numbers per power domain, it provides valuable insights into the power consumption of different components and their impact on the overall system's energy efficiency.

Additionally, this repository includes a simple usage example with dummy components to demonstrate the functionality of the Power Domain Logger.

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

4. Create the Makefile using cmake:
   ```shell
   cd imported/////////TODO

5. Build the project:
   ```shell
   make

## Usage

To use the DomainPowerModeling project, follow the instructions below:

1. Include the necessary header files in your project:
   ```cpp
   #include <DomainPowerModeling/PowerDomainLogger.h>

2. Create an instance of the PowerDomainLogger class:
   ```cpp
   power_domain_logger* <logger_instance>;

3. Creat a new instance for it:
   ```cpp
   power_domain_logger* <logger_instance> = new power_domain_logger("<logger_name>", "<location>", <timestep>);

4. Start the power logging process:
   ```cpp
   <logger_instance>->power_connector("<component_name>", "<component_type>", &(<component_instance>->powerModelPort), "<power_domain>");


## Credits

- **Paper 1**: "Fused: Closed-loop Performance and Energy Simulation of Embedded Systems" by [Sivert T. Sliper, William Wang, Nikos Nikoleris, Alex S. Weddell, and Geoff V. Merrett](https://eprints.soton.ac.uk/439059/1/fused_crp_final_PID6327977.pdf)
  - Fused is an open-source full-system simulator for energy-driven computers that accurately models the interplay between power supply, power consumption, and energy-driven execution, enabling hardware-software codesign and design space exploration.
- **Paper 2**: Title of Paper 2 ([Link](http://example.com/paper2))
  - Brief

- **Git Repository 1**: Fused ([Link](https://github.com/UoS-EEC/fused.git))
  - The repository provides the necessary code and resources to use and contribute to the Fused simulator.
- **Git Repository 2**: Name of Repository 2 ([Link](http://github.com/user/repo2))
  - Brief description or summary of the repository.

## License

This project is licensed under the [Apache License Version 2.0](LICENSE). See the [LICENSE](LICENSE) file for more details.


