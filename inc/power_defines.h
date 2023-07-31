#ifndef POWER_DEFINES_H
#define POWER_DEFINES_H

// Power annotation defines
// cpu0
#define CPU0_ENABLED                             2e-5         
#define CPU0_STALL                               0.1e-5       
#define CPU0_READ                                0.5e-11       
#define CPU0_WRITE                               1e-11         

// cpu1
#define CPU1_ENABLED                             3e-5         
#define CPU1_STALL                               0.2e-5       
#define CPU1_READ                                1e-11         
#define CPU1_WRITE                               1.5e-11       

// memory0 
#define MEM0_READ                                8e-10      
#define MEM0_WRITE                               20e-10     
#define MEM0_ON                                  40e-3     
#define MEM0_OFF                                 1e-3      

// memory1 
#define MEM1_READ                                15e-10     
#define MEM1_WRITE                               40e-10     
#define MEM1_ON                                  50e-3     
#define MEM1_OFF                                 5e-3      

#endif