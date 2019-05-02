/**
 * @file ping.h
 *
 * @brief This file is the header file for the necessary ping sensor functions
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/25/2019
 */
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <math.h>
#include "timer.h"
#include <driverlib/interrupt.h>

#ifndef PING_H_
#define PING_H_

/*
 * This function is the handler for the Timer 3B interrupt
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_TIMER3B_Handler(void);
/*
 * This function initiates the ping sensor and sets up PB3 to use the
 * ultrasonic sensor
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_init(void);
/*
 * This function sends a pulse over PB3
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
void ping_send(void);
/*
 * This function reads the pulse sent by PB3, calculates the pulse width and distance
 * from the rising and falling edges.
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @data 03/25/2019
 */
float ping_read();


#endif /* PING_H_ */
