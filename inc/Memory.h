/**
    @file Memory.h
    @brief Class to model a simple memory
    @version 1.0.0 30/06/23
*/

#pragma once

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "spdlog/spdlog.h"
#include "PowerModelChannel.hpp"
#include "PowerModelBridge.hpp"
#include "ConstantEnergyEvent.hpp"
#include "ConstantCurrentState.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class Memory : public sc_module {
public:
  tlm_utils::simple_target_socket<Memory> target_socket;

  PowerModelEventOutPort powerModelPort{"powerModelPort"};

  Memory(sc_module_name name, double read_energy_consumption, double write_energy_consumption, double state1_current, double state2_current, uint32_t size = 1000);
  ~Memory();
  sc_out<bool> irq_out;

  double read_energy_consumption;
  double write_energy_consumption;
  double state1_current;
  double state2_current;

  int m_btransportReadEventId = {-1}; // Dummy power event
  int m_btransportWriteEventId = {-1}; // Dummy power event
  int m_State1Id = {-1}; // Leakage power
  int m_State2Id = {-1}; // Leakage power

  virtual void end_of_elaboration() override;

private:
  void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay);
  void irq_thread();
  uint8_t *mem;
  uint32_t mem_size;
  sc_event send_irq;
};
