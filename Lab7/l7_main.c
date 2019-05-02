/**
 * @file l7_main.c
 *
 * @brief This file is the main file for using the ping sensor.
 * The bonus meme is able to auto-collect values and send them over UART for easy conversion
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/25/2019
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"
#include "lab5_scan_data.h"
#include "adc.h"
#include "math.h"

//Overflow variable
volatile unsigned int overflow = 0;
volatile float distance = 0;
volatile float pulse_time = 0;
volatile float pulse_ms = 0;
//Struct that will hold our bonus meme readings
float bonus_Readings[41];
float bonus_Readings_ADC[41];
float bonus_Readings_PING[41];
//String that we use to print to putty
char sendstr[40]="";
//Global integer to store value of left wheel
int left_wheel = 100;
//Global integer to store value of right wheel
int right_wheel = 100;
/*
 * This is the main function. It initiates the lcd and the ping sensor,
 * and then reads the value every 1/2 second.
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 *
 * @data 03/25/2019
 */
void main(void){
    lcd_init();
    adc_init();
    uart_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    ping_init();

    int returnedValue;
    float distance;
    int j = 0;


//    //Part 3
//   while(1){
//        ping_read(&distance, &overflow, &pulse_time, &pulse_ms);
//        //Print out the distance, amount of overflows, and the pulse width
//        lcd_printf("Distance:%.2f cm\nOverflow:%d\nPW:%.0f\nMS:%.2f",distance,overflow,pulse_time,pulse_ms);
//        //lcd_printf("%.2f", pulse_time);
//        timer_waitMillis(500);
//    }
//    //End Part 3

        //Bonus meme
        while(1){
            returnedValue = adc_read();
            //if real distance value
            if(returnedValue>0){
                //Get ping distance
                ping_read(&distance,&overflow,&pulse_time);
                //print the distance
                lcd_printf("Distance:%.2f cm\nOverflow:%d\nPulse Width:%.2f",distance,overflow,pulse_time);
                //wait a second
                timer_waitMillis(1000);
                //store the value in bonus readings
                bonus_Readings_ADC[j] = returnedValue;
                //store distance in bonus readings
                bonus_Readings_PING[j] = distance;
                //go back 5 cm
                move_backwards(sensor_data,50,left_wheel,right_wheel,0);
                //rinse wash repeat
                j++;
        }
        //Sends the data over putty
        if(j == 8){
            oi_free(sensor_data);
            int i = 0;
            int z = 0;
            for(i=0; i<9; i++){
                if(i!=0){
                    z=z+5;
                }
                  //Add all the data
                  sprintf(sendstr, "%-20f%-20f%-20d\r\n",bonus_Readings_ADC[i],bonus_Readings_PING[i],i+9+z);
                  //Send the string over UART and PUTTY
                  uart_sendStr(sendstr);
            }
            break;
        }
        //End bonus meme
    }
}
