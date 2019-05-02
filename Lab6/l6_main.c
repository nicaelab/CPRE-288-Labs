/**
 * @file l6_main.c
 *
 * @brief This file is the main file for using the IR sensor.
 * The bonus meme is able to auto-collect values and send them over UART for easy conversion
 *
 * @author Nicholas Battani, Swechha Ghimire, Veronica Torres
 *
 * @date 3/14/2019
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"
#include "lab5_scan_data.h"
#include "adc.h"
#include "math.h"


/**
 * main.c
 * Prints the button that has been pressed
 */

/*
 * This function holds the equation to find distance given an ADC value
 * @author Nick Battani, Swechha Ghimire, Veronica Torres
 *
 * @param int d
 *
 * @data 03/14/2019
 */
float getDistance(int d){
   return (99564 *pow(d,-1.158));
}

//Global integer to store value of left wheel
int left_wheel = 100;
//Global integer to store value of right wheel
int right_wheel = 100;

//Struct that will hold our readings
float readings[20];
//String that we use to print to putty
char sendstr[40]="";
float readingsADC[20];
//int value;

//Struct that will hold our bonus meme readings
float bonus_Readings[41];
float bonus_Readings_ADC[41];


void main(void){
    lcd_init();
    adc_init();
    uart_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


    int returnedValue;
    float distance;
    int j = 0;


//    //Part 2
//    while(1){
//        returnedValue = adc_read();
//        if(getDistance(returnedValue)>0){
//            distance = getDistance(returnedValue);
//            lcd_printf("Quantization Value: %i\n  Distance: %0.2f",returnedValue,distance);
//            timer_waitMillis(500);
//        }
//    }
//    //End Part 2

////Part 3
//    while(j<20){
//        returnedValue = adc_read();
//        if(getDistance(returnedValue)>0){
//            distance = getDistance(returnedValue);
//            lcd_printf("Quantization Value: %i\n  Distance: %0.2f",returnedValue,distance);
//            timer_waitMillis(100);
//            readings[j]= distance;
//            readingsADC[j]=returnedValue;
//
//            j++;
//    }
//    }
//    int i = 0;
//    for(i=0; i<20; i++){
//        //Add all the data
//        sprintf(sendstr, "%-20d%-20f%-20f\r\n",i,readings[i],readingsADC[i]);
//        //Send the string over UART and PUTTY
//        uart_sendStr(sendstr);
//    }
//    //End Part 3

    //Bonus
    while(1){
        returnedValue = adc_read();
        //if real distance value
        if(getDistance(returnedValue)>0){
            //print the quantization
            lcd_printf("Q: %i",returnedValue);
            //wait a second
            timer_waitMillis(1000);
            //store the value in bonus readings
            bonus_Readings_ADC[j] = returnedValue;
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
                  sprintf(sendstr, "%-20f%-20d\r\n",bonus_Readings_ADC[i],i+9+z);
                  //Send the string over UART and PUTTY
                  uart_sendStr(sendstr);
            }
            break;
        }
    }
    //End bonus

}
//void get_readings(){
//    value = adc_read();
//
//
//}


