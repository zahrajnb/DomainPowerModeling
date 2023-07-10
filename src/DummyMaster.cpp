/**
    @file DummyMaster.cpp
    @brief Class to generate TLM transactions
    @version 1.0.0 30/06/23
*/

#include "DummyMaster.h"

SC_HAS_PROCESS(DummyMaster);

DummyMaster::DummyMaster(sc_module_name name, uint8_t num_irqs, double enabled_power, 
  double stall_power, double read_power, double write_power)
    : sc_module(name),
      initiator_socket((string(name) + string("_initiator_socket")).c_str()),
      irqs_in((string(name) + string("_irqs_in")).c_str(), num_irqs){

  this->enabled_power = enabled_power;
  this->stall_power = stall_power;
  this->read_power = read_power;
  this->write_power = write_power;

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
    // TODO: Write event
    this->powerModelPort->reportEvent(this->c_writeEventId);
    initiator_socket->b_transport(*trans, trans_delay);
    wait(trans_delay);
    if (trans->get_response_status() != tlm::TLM_OK_RESPONSE) {
      spdlog::warn("{} write_thread() something went wrong", this->name());
      /* cout << "DummyMaster::write_thread() something went wrong\n"; */
    } else {
      /* cout << "DummyMaster::write_thread() successful\n"; */
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
    //TODO: Read event
    this->powerModelPort->reportEvent(this->c_readEventId);
    initiator_socket->b_transport(*trans, trans_delay);
    wait(trans_delay);
    if (trans->get_response_status() != tlm::TLM_OK_RESPONSE) {
      spdlog::warn("{} read_thread() something went wrong", this->name());
      /* cout << "DummyMaster::read_thread() something went wrong\n"; */
    } else {
      spdlog::info("{} read_thread(), read: {:#x}", this->name(), word);
      /* cout << "DummyMaster::read_thread, read 0x" << hex << word << "\n"; */
    }
  }
}

void DummyMaster::irq(){
  spdlog::info("{} received irq", this->name());
  /* cout << "DummyMaster, received irq\n"; */
  // TODO: Toggle module state here
  if (enabled){
    this->powerModelPort->reportState(c_enabledStateId);
    stall = ! enabled;
  } else if (stall){
    this->powerModelPort->reportState(c_stallStateId);
    enabled = ! stall;
  }
}

// Power registration
void DummyMaster::end_of_elaboration(){

  this->c_enabledStateId = this->powerModelPort->registerState(
    this->name(),
    std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("enabledState", this->enabled_power)));
  this->c_stallStateId = this->powerModelPort->registerState(
    this->name(),
    std::unique_ptr<ConstantCurrentState>(new ConstantCurrentState("stallState", this->stall_power)));
  this->c_readEventId = this->powerModelPort->registerEvent(
    this->name(),
    std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("readEvent", this->read_power)));
  this->c_writeEventId = this->powerModelPort->registerEvent(
    this->name(),
    std::unique_ptr<ConstantEnergyEvent>(new ConstantEnergyEvent("eriteEvent", this->write_power)));
}

DummyMaster::~DummyMaster() { delete trans; }
