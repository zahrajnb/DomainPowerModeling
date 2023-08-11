/**
    @file DummyMaster.cpp
    @brief Class to generate TLM transactions
    @version 1.0.0 30/06/23
*/

#include "DummyMaster.h"

SC_HAS_PROCESS(DummyMaster);

DummyMaster::DummyMaster(sc_module_name name, double state1_current, 
  double state2_current, double load_energy, double store_energy, uint8_t num_irqs)
    : sc_module(name),
      initiator_socket((string(name) + string("_initiator_socket")).c_str()),
      irqs_in((string(name) + string("_irqs_in")).c_str(), num_irqs){

  this->state1_current = state1_current;
  this->state2_current = state2_current;
  this->load_energy = load_energy;
  this->store_energy = store_energy;

  // tlm transaction payload initial setup for single word transactions
  trans = new tlm::tlm_generic_payload;
  trans->set_data_length(4);
  trans->set_streaming_width(4); // = data_length to indicate no streaming
  trans->set_byte_enable_ptr(0); // 0 indicates unused
  trans->set_dmi_allowed(false); // Mandatory initial value
  trans->set_command(tlm::TLM_IGNORE_COMMAND);
  trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  trans_delay = SC_ZERO_TIME;
  word = 0x0;
  addr = 0x0;

  SC_THREAD(write_thread);
  sensitive << write_evt;

  SC_THREAD(read_thread);
  sensitive << read_evt;

  SC_METHOD(irq);
  for (auto &irq : irqs_in) {
    sensitive << irq.posedge_event();
  }
  dont_initialize();
}


void DummyMaster::write(uint32_t write_word, uint32_t address){
  word = write_word;
  addr = address;
  write_evt.notify(SC_ZERO_TIME);
}

void DummyMaster::read(uint32_t address){
  word = 0x0;
  addr = address;
  read_evt.notify(SC_ZERO_TIME);
}

void DummyMaster::write_thread() {
  while (true) {
    wait(write_evt);
    trans->set_address(addr);
    trans->set_data_ptr(reinterpret_cast<unsigned char *>(&word));
        trans->set_command(tlm::TLM_WRITE_COMMAND);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans_delay = SC_ZERO_TIME;
    this->powerModelPort->reportEvent(this->c_storeEventId);
    initiator_socket->b_transport(*trans, trans_delay);
    wait(trans_delay);
    if (trans->get_response_status() != tlm::TLM_OK_RESPONSE) {
      spdlog::warn("{} write_thread() something went wrong", this->name());
    } else {
      spdlog::info("{} write_thread() successful", this->name());
    }
  }
}

void DummyMaster::read_thread() {
  while (true) {
    wait(read_evt);
    trans->set_address(addr);
    trans->set_data_ptr(reinterpret_cast<unsigned char *>(&word));
        trans->set_command(tlm::TLM_READ_COMMAND);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans_delay = SC_ZERO_TIME;
    this->powerModelPort->reportEvent(this->c_loadEventId);
    initiator_socket->b_transport(*trans, trans_delay);
    wait(trans_delay);
    if (trans->get_response_status() != tlm::TLM_OK_RESPONSE) {
      spdlog::warn("{} read_thread() something went wrong", this->name());
    } else {
      spdlog::info("{} read_thread(), read: {:#x}", this->name(), word);
    }
  }
}

void DummyMaster::irq(){
  spdlog::info("{} received irq", this->name());
  if (enabled){
    this->powerModelPort->reportState(c_State1Id);
    enabled = false;
  } else {
    this->powerModelPort->reportState(c_State2Id);
    enabled = true;
  }
}

// Power registration
void DummyMaster::end_of_elaboration(){

  this->c_State1Id = this->powerModelPort->registerState(
    this->name(),
    std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("State1", this->state1_current)));
  this->c_State2Id = this->powerModelPort->registerState(
    this->name(),
    std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("State2", this->state2_current)));
  this->c_loadEventId = this->powerModelPort->registerEvent(
    this->name(),
    std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("loadEvent", this->load_energy)));
  this->c_storeEventId = this->powerModelPort->registerEvent(
    this->name(),
    std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("storeEvent", this->store_energy)));
}

DummyMaster::~DummyMaster() { delete trans; }
