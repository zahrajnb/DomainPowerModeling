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
  double voltage_d1 = 0.9; 

  // modules' instantiation
  cpu0 = new DummyMaster ("cpu0", CPU0_ENABLED, CPU0_STALL, CPU0_READ, CPU0_WRITE, 2);
  bus0 = new DummyInterconnect ("bus0");
  mem0 = new Memory ("mem0", MEM0_READ, MEM0_WRITE, MEM0_ON, MEM0_OFF);
  mem1 = new Memory ("mem1", MEM1_READ, MEM1_WRITE, MEM1_ON, MEM1_OFF);

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
  cout << "power connector for cpu0 done " << std::endl;
  // MEM0
  pd1_logger->power_connector ("mem0" , "memory" , &(mem0->powerModelPort), "pd1");
  cout << "power connector for mem0 done " << std::endl;
  // MEM1
  pd1_logger->power_connector ("mem1" , "memory" , &(mem1->powerModelPort), "pd1");
  cout << "power connector for mem1 done " << std::endl;

}

PowerDomain1::~PowerDomain1(){}
