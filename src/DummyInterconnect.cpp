/**
    @file DummyInterconnect.cpp
    @brief Class to model a simple interconnect/bus system
    @version 1.0.0 30/06/23
*/

#include "DummyInterconnect.h"
DummyInterconnect::DummyInterconnect(sc_module_name name) : sc_module(name), 
target_socket((string(name) + string("_initiator_socket")).c_str()),
initiator_socket0((string(name) + string("_initiator_socket")).c_str()),
initiator_socket1((string(name) + string("_initiator_socket")).c_str()){
  target_socket.register_b_transport(this, &DummyInterconnect::b_transport);
}


void DummyInterconnect::b_transport(tlm::tlm_generic_payload &trans, sc_time &delay){

  delay += sc_time(10, SC_NS);
  sc_dt::uint64 adr = trans.get_address();

  if (adr <= 1000){
    initiator_socket0->b_transport(trans, delay);
  } else if (adr > 1000 && adr <= 2000) {
    trans.set_address(adr - 1000); //account for offset
    initiator_socket1->b_transport(trans, delay);
  }else{
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
  }
}

DummyInterconnect::~DummyInterconnect(){

}

