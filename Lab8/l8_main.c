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
    button_init();

     float degrees = 0;
     int direction = 1;
     uint8_t button = 0;
     int result = 0;
     servo_move(90);

     while(1)
     {
         button = button_getButton();
         //lcd_printf("%d",degrees);
         if(button != 0){
             timer_waitMillis(250);
             if((direction == 1 && degrees < 180) || (degrees > 0 && direction == -1)){
                 if(button == 1){
                     degrees = degrees + direction;
                 } else if(button == 2){
                     degrees += direction * 2.5;
                 } else if(button == 3){
                     degrees += direction * 5.0;
                 }
             }
             if(button == 4){
                 direction = -1 * direction;
             }
             if(button == 5){
                 degrees = 0;
             }
             if(button == 6){
                 degrees = 180;
             }
         }
         result = servo_move(degrees);
         lcd_printf("angle: %.1lf\n raw: %d\n direction: %d", degrees, result, direction);
     }




}
