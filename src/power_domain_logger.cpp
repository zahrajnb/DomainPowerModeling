/**
    @file power_domain_logger.cpp
    @brief Class to log power numbers for each domain
    @version 1.0.0 
    @date 30/06/23 
*/
#include "power_domain_logger.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_HAS_PROCESS(power_domain_logger);

power_domain_logger::power_domain_logger(const sc_module_name name,
                        const std::string logFilePath,
                        sc_time logTimestep): 
        sc_module(name),
        m_power_domain_current_LogFileName(logFilePath == "none"
                             ? "none"
                             : logFilePath + "/"  +
                                   "currentlog.csv"),
        m_logTimestep(logTimestep)
{
    if (logFilePath != "none") {
        // Make directory if it doesn't exist
        std::string makedir = "mkdir -p " + logFilePath;
        spdlog::info(logFilePath);
        system(makedir.c_str());
        // Create/overwrite log files
        std::ofstream log_file(m_power_domain_current_LogFileName, std::ios::out | std::ios::trunc);
        if (!log_file.good()) {
            SC_REPORT_FATAL(
            this->name(),
            fmt::format("Can't open current log file at {}", m_power_domain_current_LogFileName).c_str());
        } 
    }
    SC_HAS_PROCESS(power_domain_logger);
    SC_THREAD(log_process);

}

void power_domain_logger::power_connector (string moduleID, string moduleType, PowerModelEventOutPort* powerPort, string powerDomain){

    string PowerChannel_name_str = moduleID + "PowerChannel";
    string PowerBridge_name_str = moduleID + "PowerBridge";
    string Report_location = "./reports/" + powerDomain + "/" + moduleType + "/" + moduleID;
    cout << "starting to create channels and bridges" << std::endl;
    power_channels.push_back(new PowerModelChannel(PowerChannel_name_str.c_str(), Report_location, sc_time(1, SC_US)));
    power_bridges.push_back(new PowerModelBridge(PowerBridge_name_str.c_str(), sc_time(1, SC_US)));

    PowerModelChannel *module_p_channel = power_channels.back();
    PowerModelBridge *module_p_bridge = power_bridges.back();
    
    sc_signal<double>* current_bind = new sc_signal<double>();
    
    module_p_bridge->v_in.bind(voltage);
    module_p_bridge->i_out.bind(*current_bind);

    // Creating a new struct to save the current value and the module ID in the vector
    CurrentModule* currentModule = new CurrentModule;
    currentModule->module_current = current_bind; // Read the initial value of the signal
    currentModule->moduleID = moduleID;
    currents.push_back(currentModule);

    module_p_bridge->powerModelPort.bind(*(module_p_channel));
    (*powerPort).bind(*(module_p_channel));
    cout << "power port binded " << std::endl;    
}

void power_domain_logger::log_process() {
    double sum = 0.0;
    std::vector<std::string> savedModuleIDs;  // Vector to store previously saved moduleIDs

    while (1) {
        wait(m_logTimestep);
        // Go through my whole vector elements check the module_current value the first time when gets a velue other than 0 and add that value to the sum only once per moduleID
        // Iterate over the currents vector
        for (const auto& currentModule : currents) {
            double currentVal = currentModule->module_current->read();
            std::string currentModuleID = currentModule->moduleID;
            std::cout << "Module ID: " << currentModuleID << std::endl;
            std::cout << "Module Current: " << currentVal << std::endl;

            // Check if the moduleID is already saved
            if (currentVal != 0.0 && std::find(savedModuleIDs.begin(), savedModuleIDs.end(), currentModuleID) == savedModuleIDs.end()) {
                // Adds all the values of current from modules in each domain calling the power_connector
                sum += currentVal;
                total_current.write(sum);
                savedModuleIDs.push_back(currentModuleID);
                cout << "*************accumulated current is*************: " << total_current << std::endl;
                
            }
        }
        // Call dumpCurrentCsv to write the vector to the CSV file
        dumpCurrentCsv();
        cout << "*************accumulated current is*************: " << total_current << std::endl;
    }
}

void power_domain_logger::dumpCurrentCsv()
{
    std::ofstream log_file(m_power_domain_current_LogFileName, std::ios::out | std::ios::app);
    // Write elements of the currents vector to the CSV file
    if (log_file.tellp() == 0) {
        // Header
        log_file << "moduleID,module_current,time(s)\n";
    }
    // Values
    for (const auto& module : currents) {
        log_file << module->moduleID << ",";
        log_file << module->module_current->read() << ",";
        log_file << sc_time_stamp().to_seconds() << "\n";
    }
    log_file.close();  // Close the file
}

power_domain_logger::~power_domain_logger()
{
    // deleting the pointers 
    for (PowerModelChannel* channel_ptr : power_channels) {
        delete channel_ptr;
    }
    for (PowerModelBridge* bridge_ptr : power_bridges) {
        delete bridge_ptr;
    }
}

