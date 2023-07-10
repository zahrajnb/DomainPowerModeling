/**
    @file dut_top.h
    @brief Class to model the top level hierarchy
    @version 1.0.0 30/06/23
*/

#pragma once

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "PowerDomain1.h"
#include "PowerDomain2.h"
#include <random>

class Dut_top : public sc_module {
public:
  Dut_top(sc_module_name name);
  ~Dut_top();
  PowerDomain1 pd1;
  PowerDomain2 pd2;

private:
  void pd1_thread();
  void pd2_thread();
  std::random_device rd;
  bool generate_random_transaction();
  uint32_t generate_random_address(int max = 1000);
  uint32_t generate_random_payload();
};
