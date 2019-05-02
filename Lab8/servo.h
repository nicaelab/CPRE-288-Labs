/**
 * @file servo.h
 *
 * @brief This file is the header file for using the servo. It is configured for ROBOT 6
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 4/2/2019
 */
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <math.h>
#include "timer.h"
#include <driverlib/interrupt.h>


#ifndef SERVO_H_
#define SERVO_H_

/*
 * This is the servo init function. It sets up the GPIO and Timer to
 * use the servo.
 *
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 *
 * @data 4/2/2019
 */
void servo_init();
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
int servo_move(float degrees);


#endif /* SERVO_H_ */
