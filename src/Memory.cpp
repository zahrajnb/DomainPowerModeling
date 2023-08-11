/**
    @file Memory.cpp
    @brief Class to model a simple memory
    @version 1.0.0 30/06/23
*/

#include "Memory.h"

SC_HAS_PROCESS(Memory);

Memory::Memory(sc_module_name name, double read_energy_consumption, double write_energy_consumption, 
double state1_current, double state2_current, uint32_t size)
    : sc_module(name), read_energy_consumption(read_energy_consumption), write_energy_consumption(write_energy_consumption), 
      state1_current(state1_current), state2_current(state2_current),
      target_socket((string(name) + string("_target_socket")).c_str()),
      irq_out((string(name) + string("_irq_out")).c_str()) {
  mem_size = size;
  mem = new uint8_t[mem_size];
  target_socket.register_b_transport(this, &Memory::b_transport);

  SC_THREAD(irq_thread);
  sensitive << send_irq;
}

Memory::~Memory(){
  delete mem;
}

void Memory::b_transport(tlm::tlm_generic_payload &trans, sc_time &delay){

  delay += sc_time(10, SC_NS);
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64 adr = trans.get_address();
  unsigned char *ptr = trans.get_data_ptr();
  uint32_t len = trans.get_data_length();
  uint32_t wid = trans.get_streaming_width();
  unsigned char *byt = trans.get_byte_enable_ptr();
  uint32_t aux_value = 0;
  // Standard checks:
  if (byt) {
    trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
    return;
  }
  if (len > sizeof(aux_value) || wid < len) {
    trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    return;
  }
  if (adr >= sc_dt::uint64(mem_size)){
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
    return;
  }
  if (cmd == tlm::TLM_READ_COMMAND){
    memcpy(ptr, &mem[adr], len);
    spdlog::info("{} read", this->name());
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    this->powerModelPort->reportEvent(m_btransportReadEventId);
  }else if (cmd == tlm::TLM_WRITE_COMMAND){
    memcpy(&mem[adr], ptr, len);
    spdlog::info("{} write", this->name());
    this->powerModelPort->reportEvent(m_btransportWriteEventId);
    if (adr <= 100){
      //fire IRQ
      send_irq.notify(SC_ZERO_TIME);
      spdlog::info("{} firing IRQ", this->name());
    }else if (adr > 100 && adr<= 200) {
      //TODO: change to state1
      spdlog::info("{} state 1", this->name());
      this->powerModelPort->reportState(m_State1Id);
    
    } else if (adr > 200 && adr<= 300) {
      //TODO: change to state2
      spdlog::info("{} state 2", this->name());
      this->powerModelPort->reportState(m_State2Id);

    }
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  }else {
    trans.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
    return;
  }
}

void Memory::irq_thread(){
  while (true) {
    wait(send_irq);
    irq_out.write(true);
    wait(5,SC_NS);
    irq_out.write(false);
  }
}

void Memory::end_of_elaboration(){
  // The events are assigned in a fixed order from array (in case of having many events). 
  // If only a few events are defined, could probably have one parameter for each event.
  this->m_btransportReadEventId = this->powerModelPort->registerEvent(
          this->name(), 
          std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("m_btransportReadEventId", read_energy_consumption))); // unique_ptr instead of make_unique due to c++ version
  this->m_btransportWriteEventId = this->powerModelPort->registerEvent(
          this->name(), 
          std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("m_btransportWriteEventId", write_energy_consumption)));
  this->m_State1Id = this->powerModelPort->registerState(
          this->name(), 
          std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("m_State1Id", state1_current)));
  this->m_State2Id = this->powerModelPort->registerState(
          this->name(), 
          std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("m_State2Id", state2_current)));
}