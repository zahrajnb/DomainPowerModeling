/**
    @file PowerDomain1.h
    @brief Class to model a power domain
    @version 1.0.0 30/06/23
*/

#pragma once

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "DummyInterconnect.h"
#include "DummyMaster.h"
#include "Memory.h"
#include "power_domain_logger.h"
#include "power_defines.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class PowerDomain1 : public sc_module {
public:
  PowerDomain1(sc_module_name name);
  ~PowerDomain1();
  DummyMaster* cpu0;
  DummyInterconnect* bus0;
  Memory* mem0;
  Memory* mem1;
  power_domain_logger* pd1_logger;

};
