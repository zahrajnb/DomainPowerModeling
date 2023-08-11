/**
    @file PowerDomain2.cpp
    @brief Class to model a power domain
    @version 1.0.0 30/06/23
*/

#include "PowerDomain2.h"

SC_HAS_PROCESS(PowerDomain2);

PowerDomain2::PowerDomain2(sc_module_name name)
    : sc_module(name){

  // Domain voltage
  double voltage_d2 = 2; 

  // modules' instantiation
  cpu0 = new DummyMaster ("cpu0", PD2_CPU0_STATE1, PD2_CPU0_STATE2, PD2_CPU0_LOAD, PD2_CPU0_STORE, 1);
  cpu1 = new DummyMaster ("cpu1", PD2_CPU1_STATE1, PD2_CPU1_STATE2, PD2_CPU1_LOAD, PD2_CPU1_STORE, 1);
  mem0 = new Memory ("mem0", PD2_MEM0_READ, PD2_MEM0_WRITE, PD2_MEM0_STATE1, PD2_MEM0_STATE2);
  mem1 = new Memory ("mem1", PD2_MEM1_READ, PD2_MEM1_WRITE, PD2_MEM1_STATE1, PD2_MEM1_STATE2);

  //signal binding
  mem0->irq_out.bind(cpu0->irqs_in[0]);
  mem1->irq_out.bind(cpu1->irqs_in[0]);

 // TLM port binding
 cpu0->initiator_socket.bind(mem0->target_socket);
 cpu1->initiator_socket.bind(mem1->target_socket);

 // Power domain logger instantiation
  pd2_logger = new power_domain_logger("pd2_logger", voltage_d2, "../reports/domain_currents/pd2", sc_time(1, SC_US));

  // Power logger connections for power domain 2
  // CPU0
  pd2_logger->power_connector ("cpu0" , "cpu" , &(cpu0->powerModelPort), "pd2");
  spdlog::info("power connector for cpu0 pd2 done");
  // CPU1
  pd2_logger->power_connector ("cpu1" , "cpu" , &(cpu1->powerModelPort), "pd2");
  spdlog::info("power connector for cpu1 pd2 done");
  // MEM0
  pd2_logger->power_connector ("mem0" , "memory" , &(mem0->powerModelPort), "pd2");
  spdlog::info("power connector for mem0 pd2 done");
  // MEM1
  pd2_logger->power_connector ("mem1" , "memory" , &(mem1->powerModelPort), "pd2");
  spdlog::info("power connector for mem1 pd2 done");
}

PowerDomain2::~PowerDomain2() {}
