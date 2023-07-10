/**
    @file DummyInterconnect.h
    @brief Class to model a simple interconnect/bus system
    @version 1.0.0 30/06/23
*/

#pragma once

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

class DummyInterconnect : public sc_module {
public:
  tlm_utils::simple_target_socket<DummyInterconnect> target_socket;
  tlm_utils::simple_initiator_socket<DummyInterconnect> initiator_socket0;
  tlm_utils::simple_initiator_socket<DummyInterconnect> initiator_socket1;

  PowerModelEventOutPort powerModelPort{"powerModelPort"};

  DummyInterconnect(sc_module_name name);
  ~DummyInterconnect();

private:
  void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay);
};
