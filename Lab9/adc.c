/**
 * @file adc.c
 *
 * @brief This file is the .c file for ADC functions.
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/14/2019
 */
#include "adc.h"
/*
 * This function initiates the ADC
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/14/2019
 */
void adc_init(void){
    //enable clock for port B (PB4, AIN10 for input signal) (1 of 6)
    SYSCTL_RCGCGPIO_R |= 0b000010;

    //enable clock for ADC0 (bit 0 of only 2)
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port B pin 4 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0x10;

    //set pin 4 port B to input (0)
    GPIO_PORTB_DIR_R &= 0b11101111;

    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |= 0x10;

    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS1 sample sequencer to configure it
    ADC0_ACTSS_R &= ~(0x00000002);

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R &= ~(0x000000F0);

    //set 1st sample to use the AIN10 ADC pin (8 MUX samples, 12 analog pins)
    ADC0_SSMUX1_R |= 0x000A;

    //enable raw interrupt status, 1st sample raw interrupt enable bit 2, 1st sample is end of sequence bit 1
    ADC0_SSCTL1_R |= (0x0004 | 0x0002);

    //enable oversampling to average 0x0 or 16X
    //ADC0_SAC_R |= 0x0;
    ADC0_SAC_R |= 0x4;

    //clear interrupt flags
    ADC0_ISC_R |= 0x00000002;

    //enable    ADC0SS1 interrupt
    ADC0_IM_R |= 0x00000002;

    //re-enable ADC0 SS1
    ADC0_ACTSS_R |= 0x00000002;
}
/*
 * This function reads values from the ADC
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/14/2019
 */
int adc_read(void){
    //initiate SS1 conversion
    ADC0_PSSI_R = ADC_PSSI_SS1;
    //wait for ADC conversion to be complete
    while ((ADC0_RIS_R & ADC_RIS_INR1) == 0)
    {
        //wait
    }
    //grab result
    int value = (ADC0_SSFIFO1_R & 0x0FFF);
    ADC0_ISC_R = ADC_ISC_IN1;
    return value;
}



