/**
 * @file adc.h
 *
 * @brief This file is the header file for the ADC
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/14/2019
 */
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

#ifndef ADC_H_
#define ADC_H_
/*
 * This function initiates the ADC
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/14/2019
 */
void adc_init(void);
/*
 * This function reads values from the ADC
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/14/2019
 */
int adc_read(void);



#endif /* ADC_H_ */
