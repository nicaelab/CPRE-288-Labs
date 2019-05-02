/**
 * @file ping.c
 *
 * @brief This file is the c file for the necessary ping sensor functions
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/25/2019
 */
#include "ping.h"

//Enum to hold the state values of sensor
volatile enum {STATE_LOW, STATE_HIGH, STATE_FINISHED} state;
//Start time of pulse
volatile unsigned rising_edge;
//End time of pulse
volatile unsigned falling_edge;

volatile float *distance_ptr;
volatile int *overflow_ptr;
volatile float *pulse_time_ptr;
volatile float *pulse_ms_ptr;



/*
 * This function is the handler for the Timer 3B interrupt
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_TIMER3B_Handler(void) {
    TIMER3_ICR_R = TIMER_ICR_CBECINT;
    if (state == STATE_LOW) {
        rising_edge = TIMER3_TBR_R;
        state = STATE_HIGH;
        return;
    } if (state == STATE_HIGH) {
        falling_edge = TIMER3_TBR_R;
        state = STATE_FINISHED;
        TIMER3_CTL_R &= 0xFEFF;
        return;
    }
        return;
}

/*
 * This function initiates the ping sensor and sets up PB3 to use the
 * ultrasonic sensor
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_init(void) {
    //Enable Port B
    SYSCTL_RCGCGPIO_R |= 0x2;
    //Digital enable PB3
    GPIO_PORTB_DEN_R |= 0x08;
    //Enable the alternate function for PB3
    GPIO_PORTB_AFSEL_R |= 0x08;
    //Set the alternate function of PB3 to timer3
    GPIO_PORTB_PCTL_R |= 0x7000;
    //Set PB3 to an output
    GPIO_PORTB_DIR_R |= 0x08;
    //Enable input capture
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;
    //Enable timer3
    TIMER3_CTL_R &= 0xFEFF;
    //Turn on edge select
    TIMER3_CTL_R |= 0x0C00;
    //Set the timer to 16 bit mode
    TIMER3_CFG_R |= 0x04;
    //Set capture, edge-time, and count up
    TIMER3_TBMR_R |= 0b010111;
    TIMER3_TBPR_R = 0xFF;
    //Set the upper bound
    TIMER3_TBILR_R = 0xFFFF;
    //Turn on the capture interrupt
    TIMER3_IMR_R |= 0x00000400;
    //Clear the interrupt
    TIMER3_ICR_R |= 0x00000400;
    //Enable NVIC interrupt table
    NVIC_EN1_R = 0x010;
    //Bind the interrupt to the interrupt handler
    IntRegister(INT_TIMER3B, ping_TIMER3B_Handler);
    IntMasterEnable();
}

/*
 * This function sends a pulse over PB3
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_send() {
    //Turn off the alternate function for PB3
    GPIO_PORTB_AFSEL_R &= 0xF7;
    //Set PB3 as an output
    GPIO_PORTB_DIR_R |= 0x08;
    //Set the PB3 to a rising edge
    GPIO_PORTB_DATA_R |= 0x08;

    //Wait 5 milliseconds
    timer_waitMillis(5);

    //Set PB3 to falling edge
    GPIO_PORTB_DATA_R &= 0xF7;
    //Set PB3 to an input
    GPIO_PORTB_DIR_R &= 0xF7;
    //Turn back on the alternate function
    GPIO_PORTB_AFSEL_R |= 0x08;
    //Set the state to lowing
    state = STATE_LOW;
    //Set the control register
    TIMER3_CTL_R |= 0b0100000000;
}

/*
 * This function reads the pulse sent by PB3, calculates the pulse width and distance
 * from the rising and falling edges.
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
float ping_read() {

    float distance = 0;
    int overflow = 0;
    float pulse_time = 0;
    //float pulse_ms = 0;
    //Send starting pulse
    ping_send();

    //Variable to store the time of of the pulse
    pulse_time = falling_edge - rising_edge;

    //Detect overflow and adjust for it
    if (rising_edge > falling_edge) {
        overflow = overflow + 1;
        pulse_time = pulse_time + 0xFFFFFF;
    }

    //pulse_ms = (pulse_time / 16000.0);
    //Calculate the distance
    distance = ((pulse_time / 16000000.0) * 34300.0)/2;
    //lcd_printf("dist:%.2f\npt:%",distance);

     return distance;
}



