#include "dut_top.h"

int sc_main(int argc, char *argv[]) {
  Dut_top top("top");
  sc_start(500, SC_US);
  return 0;
}
