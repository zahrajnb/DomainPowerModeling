/**
    @file DummyMaster.h
    @brief Class to generate TLM transactions
    @version 1.0.0 30/06/23
*/

#pragma once

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "spdlog/spdlog.h"
#include "PowerModelChannel.hpp"
#include "PowerModelBridge.hpp"
#include "ConstantEnergyEvent.hpp"
#include "ConstantCurrentState.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class DummyMaster : public sc_module {
public:
  tlm_utils::simple_initiator_socket<DummyMaster> initiator_socket;

  PowerModelEventOutPort powerModelPort{"powerModelPort"};

  double state1_current;
  double state2_current;
  double load_energy;
  double store_energy;

  DummyMaster(sc_module_name name, double state1_current, double state2_current, 
  double load_energy,double store_energy, uint8_t num_irqs = 1);

  ~DummyMaster();

  void write(uint32_t write_word, uint32_t address);
  void read(uint32_t address);

  sc_vector<sc_signal<bool>> irqs_in;

  
  bool enabled{};

  int c_State1Id{-1};
  int c_State2Id{-1};
  int c_loadEventId{-1};
  int c_storeEventId{-1};

  virtual void end_of_elaboration() override;

private:

  void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay);
  void write_thread();
  void read_thread();
  void irq();
  tlm::tlm_generic_payload *trans;
  sc_time trans_delay;
  uint32_t word;
  uint32_t addr;
  sc_event write_evt;
  sc_event read_evt;
};

