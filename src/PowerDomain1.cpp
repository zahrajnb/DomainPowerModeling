/**
    @file PowerDomain1.cpp
    @brief Class to model a power domain
    @version 1.0.0 30/06/23
*/

#include "PowerDomain1.h"

SC_HAS_PROCESS(PowerDomain1);

PowerDomain1::PowerDomain1(sc_module_name name)
    : sc_module(name){

  // Domain voltage
  double voltage_d1 = 2.6; 

  // modules' instantiation
  cpu0 = new DummyMaster ("cpu0", PD1_CPU0_STATE1, PD1_CPU0_STATE2, PD1_CPU0_LOAD, PD1_CPU0_STORE, 2);
  bus0 = new DummyInterconnect ("bus0");
  mem0 = new Memory ("mem0", PD1_MEM0_READ, PD1_MEM0_WRITE, PD1_MEM0_STATE1, PD1_MEM0_STATE2);
  mem1 = new Memory ("mem1", PD1_MEM1_READ, PD1_MEM1_WRITE, PD1_MEM1_STATE1, PD1_MEM1_STATE2);

  // signal binding
  mem0->irq_out.bind(cpu0->irqs_in[0]);
  mem1->irq_out.bind(cpu0->irqs_in[1]);

  // TLM port binding
  cpu0->initiator_socket.bind(bus0->target_socket);
  bus0->initiator_socket0.bind(mem0->target_socket);
  bus0->initiator_socket1.bind(mem1->target_socket);

  // Power domain logger instantiation
  pd1_logger = new power_domain_logger("pd1_logger", voltage_d1 , "../reports/domain_currents/pd1", sc_time(1, SC_US));

  // Power logger connections for power domain 1
  // CPU0
  pd1_logger->power_connector ("cpu0" , "cpu" , &(cpu0->powerModelPort), "pd1");
  spdlog::info("power connector for cpu0 pd1 done");
  // MEM0
  pd1_logger->power_connector ("mem0" , "memory" , &(mem0->powerModelPort), "pd1");
  spdlog::info("power connector for mem0 pd1 done");
  // MEM1
  pd1_logger->power_connector ("mem1" , "memory" , &(mem1->powerModelPort), "pd1");
  spdlog::info("power connector for mem1 pd1 done");

}

PowerDomain1::~PowerDomain1(){}
