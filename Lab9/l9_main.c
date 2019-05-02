/**
 * @file l8_main.c
 *
 * @brief This file is the main file for using the servo. It is configured for ROBOT 6
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 4/2/2019
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"
#include "lab5_scan_data.h"
#include "adc.h"
#include "math.h"
#include "ping.h"
#include "servo.h"


/*
 * This is the main function. It initiates the lcd, servo, and buttons,
 * and then allows you to maniupulate the servo based on button press.
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 *
 * @data 4/2/2019
 */


void main(void){
    lcd_init();
    servo_init();
    adc_init();
    ping_init();
    uart_init();

    timer_waitMillis(5);
    full_scan();
    print_UART();
    find_smallest();
}
