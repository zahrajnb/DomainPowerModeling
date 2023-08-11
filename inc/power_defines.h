#ifndef POWER_DEFINES_H
#define POWER_DEFINES_H

// Power annotation defines

// Power Domain 1
// cpu0      
#define PD1_CPU0_LOAD                                1.5e-12       
#define PD1_CPU0_STORE                               2e-12      
#define PD1_CPU0_STATE1                              1e-6         
#define PD1_CPU0_STATE2                              0.5e-6        

// memory0 
#define PD1_MEM0_READ                                10e-12      
#define PD1_MEM0_WRITE                               11e-12     
#define PD1_MEM0_STATE1                              14e-6     
#define PD1_MEM0_STATE2                              8.5e-6      

// memory1 
#define PD1_MEM1_READ                                50e-12     
#define PD1_MEM1_WRITE                               60e-12     
#define PD1_MEM1_STATE1                              60e-6     
#define PD1_MEM1_STATE2                              30e-6  

// Power Domain 2
// cpu0      
#define PD2_CPU0_LOAD                                1.2e-12       
#define PD2_CPU0_STORE                               1.6e-12      
#define PD2_CPU0_STATE1                              0.8e-6         
#define PD2_CPU0_STATE2                              0.4e-6    

// cpu1 
#define PD2_CPU1_LOAD                                1e-12         
#define PD2_CPU1_STORE                               1.1e-12
#define PD2_CPU1_STATE1                              1e-6         
#define PD2_CPU1_STATE2                              0.6e-6             

// memory0 
#define PD2_MEM0_READ                                8e-12      
#define PD2_MEM0_WRITE                               9e-12     
#define PD2_MEM0_STATE1                              11e-6     
#define PD2_MEM0_STATE2                              6.5e-6      

// memory1 
#define PD2_MEM1_READ                                40e-12     
#define PD2_MEM1_WRITE                               48e-12     
#define PD2_MEM1_STATE1                              48e-6     
#define PD2_MEM1_STATE2                              24e-6      

#endif