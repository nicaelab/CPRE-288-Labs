/**
 * @file servo.c
 *
 * @brief This file contains the functions to use the servo. It is configured for ROBOT 6
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 4/2/2019
 */

#include "servo.h"

//Double multiplied by degrees that says how many clock ticks are a degree
double modifier = 150;
//Start value (0 degrees)
int start = 10000;

/*
 * This is the servo init function. It sets up the GPIO and Timer to
 * use the servo.
 *
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 *
 * @data 4/2/2019
 */
void servo_init(){
    //Enable port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //Enable alternate function for PB5
    GPIO_PORTB_AFSEL_R |= 0x20;
    //Enable desired alternate function for PB5
    GPIO_PORTB_PCTL_R |= 0x700000;
    //Set the direction to an output for PB5
    GPIO_PORTB_DIR_R |= 0x20;
    //Enable PB5 for digital
    GPIO_PORTB_DEN_R |= 0x20;
    //Enable the timer
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;
    //Disable timer1 while we set it up
    TIMER1_CTL_R &= 0xFEFF;
    //Set up for a 16-bit timer
    TIMER1_CFG_R |= 0x04;
    //Enable PWM, Capture mode, and one shot timer mode
    TIMER1_TBMR_R |= 0x0000000A;
    //Set timer start
    TIMER1_TBPR_R = (320000 >> 16) & 0xFF;
    //First 16 bits
    TIMER1_TBILR_R = 320000 & 0xFFFF;
    //Remaining 8 bits
    TIMER1_TBPMR_R = 0x00;
    //Set match value
    TIMER1_TBMATCHR_R = 0x3E80;
    //Reenable the timer
    TIMER1_CTL_R |= 0x0100;

}

/*
 * This is the servo_move function. It takes in a float of degrees
 * and converts this degrees into a clock cycle count. It then loads
 * that clock cycle count into the match register and moves the servo
 * to the necessary degree.
 *
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @param float Degrees
 *
 * @data 4/2/2019
 */
int servo_move(float degrees){
    int result = 320000 - (start + (modifier * degrees));
    TIMER1_TBMATCHR_R = result & 0xFFFF;
    TIMER1_TBPMR_R = (result >> 16) &0xFF;
    return result;
}
