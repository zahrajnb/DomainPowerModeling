/**
    @file dut_top.cpp
    @brief Class to model the top level hierarchy
    @version 1.0.0 30/06/23
*/

#include "dut_top.h"

SC_HAS_PROCESS(Dut_top);

Dut_top::Dut_top(sc_module_name name) : sc_module(name), pd1("pd1"), pd2("pd2"){
  SC_THREAD(pd1_thread);
  SC_THREAD(pd2_thread);
}

uint32_t Dut_top::generate_random_address(int max){
  uint32_t address = 0;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> ud {0, max};
  return (uint32_t)(ud(gen));
}

bool Dut_top::generate_random_transaction() {
  std::mt19937 gen(rd());
  std::bernoulli_distribution bd(0.5);
  return bd(gen);
}

uint32_t Dut_top::generate_random_payload(){
  return (uint32_t)rand();
}

void Dut_top::pd1_thread(){
  while(true){
    wait(50, SC_NS);
    uint32_t address = 0x0;
    bool read_or_write = generate_random_transaction();
    address = generate_random_address(2000); 
    if (read_or_write) {
      //read
      pd1.cpu0->read(address);
    }else {
      //write
      uint32_t data = generate_random_payload();
      pd1.cpu0->write(data, address);
    }
  }
}

void Dut_top::pd2_thread(){
  while(true){
    wait(100, SC_NS);
    uint32_t address = 0x0;
    bool read_or_write = generate_random_transaction();
    address = generate_random_address(); 
    if (read_or_write) {
      //read
      pd2.cpu0->read(address);
    }else {
      //write
      uint32_t data = generate_random_payload();
      pd2.cpu0->write(data, address);
    }
    read_or_write = generate_random_transaction();
    address = generate_random_address(); 
    if (read_or_write) {
      //read
      pd2.cpu1->read(address);
    }else {
      //write
      uint32_t data = generate_random_payload();
      pd2.cpu1->write(data, address);
    }
  }
}

Dut_top::~Dut_top() {}
