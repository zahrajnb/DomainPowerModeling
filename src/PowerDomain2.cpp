/**
    @file PowerDomain2.cpp
    @brief Class to model a power domain
    @version 1.0.0 30/06/23
*/

#include "PowerDomain2.h"

SC_HAS_PROCESS(PowerDomain2);

PowerDomain2::PowerDomain2(sc_module_name name)
    : sc_module(name){

  // modules' instantiation
  cpu0 = new DummyMaster ("cpu0", CPU0_ENABLED, CPU0_STALL, CPU0_READ, CPU0_WRITE, 1);
  cpu1 = new DummyMaster ("cpu1", CPU1_ENABLED, CPU1_STALL, CPU1_READ, CPU1_WRITE, 1);
  mem0 = new Memory ("mem0", MEM0_READ, MEM0_WRITE, MEM0_ON, MEM0_OFF);
  mem1 = new Memory ("mem1", MEM1_READ, MEM1_WRITE, MEM1_ON, MEM1_OFF);

  //signal binding
  mem0->irq_out.bind(cpu0->irqs_in[0]);
  mem1->irq_out.bind(cpu1->irqs_in[0]);

 // TLM port binding
 cpu0->initiator_socket.bind(mem0->target_socket);
 cpu1->initiator_socket.bind(mem1->target_socket);

 // Power domain logger instantiation
  pd2_logger = new power_domain_logger("pd2_logger", "../reports/domain_currents/pd2", sc_time(50, SC_NS));

  // Power logger connections for power domain 2
  // CPU0
  pd2_logger->power_connector ("cpu0" , "cpu" , &(cpu0->powerModelPort), "pd2");
  cout << "power connector for cpu0 done " << std::endl;
  // CPU1
  pd2_logger->power_connector ("cpu1" , "cpu" , &(cpu1->powerModelPort), "pd2");
  cout << "power connector for cpu1 done " << std::endl;
  // MEM0
  pd2_logger->power_connector ("mem0" , "memory" , &(mem0->powerModelPort), "pd2");
  cout << "power connector for mem0 done " << std::endl;
  // MEM1
  pd2_logger->power_connector ("mem1" , "memory" , &(mem1->powerModelPort), "pd2");
  cout << "power connector for mem1 done " << std::endl;
}

PowerDomain2::~PowerDomain2() {}
