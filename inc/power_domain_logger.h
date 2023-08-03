/**
    @headerfile power_domain_logger.h
    @brief Class to log power numbers for each domain
    @version 1.0.0 
    @date 30/06/23
*/
#ifndef __POWER_DOMAIN_LOGGER_H__
#define __POWER_DOMAIN_LOGGER_H__

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "PowerModelChannel.hpp"
#include "PowerModelBridge.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/**
   *  @class Field
   *  @brief Class that models bitfields and their attributes
   */
class power_domain_logger: sc_module {
public:

    
    /**
    *  @brief power_domain_logger constructor
    *  @param name Name of the power_domain_logger
    *  @param logFilePath address for saving the currents into .csv file
    *  @param logTimestep time step to write the csv-formatted log of currents
    */
    
    power_domain_logger(const sc_module_name name,
                const double domainVoltage,
                const std::string logFilePath = "",
                const sc_core::sc_time logTimestep = sc_core::SC_ZERO_TIME);

    /**
    *  @brief power_domain_logger destructor
    */
    ~power_domain_logger();

    /**
     * @brief A map to associate each power domain with its corresponding total current
     */
    map<std::string, double> total_current_per_domain;

    sc_signal<double> voltage{"voltage"};
    // sc_core::sc_in<double> voltage{"voltage"};
    double domainVoltage;

    double temp_current;

    // Logging 
    std::string m_power_domain_current_LogFileName;

    // Log file timestep
    sc_core::sc_time m_logTimestep;

    /**
    *  @brief Struct to save the module name and the value of current for each module
    */
    struct CurrentModule {
        sc_signal<double>* module_current;
        std::string moduleID;
        std::string powerDomain;
    };

    /**
    *  @brief Vector containing all the current structs
    */
    vector<CurrentModule*> currents;
    /**
    *  @brief Vector containing all the power channels
    */
    vector<PowerModelChannel*> power_channels;
    /**
    *  @brief Vector containing all the power bridges
    */
    vector<PowerModelBridge*> power_bridges;

    /**
    *  @brief A method that writes the current for each module in each power domain to a csv
    */
    void dumpCurrentCsv();


    /**
    *  @brief function to creat the power channels and power bridges based on fused and make the connections
    *  @param moduleID Name of the componant
    *  @param moduleType Type of the componant if it is memory, cpu, peripheral, ...
    *  @param powerPort Pointer to power port of the componant to pass the power values and do the connections
    *  @param powerDomain Power domain that the componant is working at
    */
    void power_connector (std::string moduleID, std::string moduleType, PowerModelEventOutPort* powerPort, string powerDomain);

private:

    /**
    *  @brief systemC thread to check the values for current in each componant at diffrent time and add them to the total current
    */
    void log_process();
    
};
#endif