/**
 * @file l4_main.c
 *
 * @brief This file is the main file that initiates the uart for communication.
 * The bonus meme section can drive the robot forward and backwards.
 *
 * @author Nicholas Battani, Swechha Ghimire
 *
 * @date 2/27/2019
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"

volatile int uart_event = 0; // Boolean to keep track of whether a hardware event has happened
volatile char uart_char = ""; // keeps track of character that is sent


/**
 * main.c
 * Prints the button that has been pressed
 */
void main(void) {
         //Initiate the uart, lcd, open interface, and uart interrupts
         uart_init();
         lcd_init();

         oi_t *sensor_data = oi_alloc();
         oi_init(sensor_data);

         uart_interrupts_init(&uart_event,&uart_char);

         //Part 1,2
//         int i = 0, j =0 ;
//         char message[21], final[21];
//         message[20] = '\0';
//         final[20] = '\0';
//
//
//         while(1){
//             if(i < 20){ //less than 20 characters
//                  message[i] = uart_receive();
//                  if(message[i] ==  '\r'){ //if it's a return
//                      message[i] = '\0'; //set it to null
//                      uart_sendChar('\r'); // send a return
//                      uart_sendChar('\n'); // send a new line
//                      for (j=0;j<=i;j++){ // print the message
//                           final[j]=message[j];
//                      }
//                      lcd_printf("%s", final); //print the letter
//                      i = 0;
//                  }
//                  else{
//                       uart_sendChar(message[i]);
//                      lcd_printf("char: %c\nindex: %d",message[i],i); //print out count and letter
//                       i++;
//                  }
//
//             }
//             else{
//                  message[i] = '\0'; //set to null
//                  uart_sendChar('\r');//send return
//                  uart_sendChar('\n'); //send new line
//                  lcd_printf("%s", message);//print the message
//                  for(j=0;j<=1;j++){
//                      final[j]=message[j];
//                  }
//                  i = 0;
//             }
//         }
         //End part 1,2

         //Part 3
         while(1){
             //If interrupt flag is triggered
             if(uart_event==1){
                 //Part 3
                 //Print the character received on LCD
//                 lcd_printf("CHAR RECEIVED:%c",uart_char);
//                 //Send back
//                 uart_sendChar('\n');
//                 uart_sendChar(uart_char);
//                 //Set the flag equal to zero
//                 uart_event = 0;
                 //Part 3
                 //BONUS MEME

                 //If the character received is w
                 if(uart_char == 'w'){
                     //Print drive forward
                     lcd_printf("Drive Forward");
                     //Drive forward
                     move_forward(sensor_data,100,250,250,0);
                     //Send string over UART
                     uart_sendStr("\nYou Drove Forward");
                     //Set flag equal to zero
                     uart_event = 0;
                 }
                 //If the character received is s
                 if(uart_char == 's'){
                     //Print drive backward
                     lcd_printf("Drive Backward");
                     //Drive backwards
                     move_backwards(sensor_data,100,250,250,0);
                     //Send string over UART
                     uart_sendStr("\nYou Drove Backwards");
                     //Set flag equal to zero
                     uart_event = 0;
                 }
                 //If the character received is d
                 if(uart_char == 'd'){
                     //Print that you're turning
                     lcd_printf("Turn 90 Clockwise");
                     //Turn clockwise
                     move_turn_clockwise(sensor_data,90);
                     //Send string over UART
                     uart_sendStr("\nYou Turned Clockwise");
                     //Set flag equal to zero
                     uart_event = 0;
                 }
                 //If the character received is a
                 if(uart_char == 'a'){
                     //Print that you're turning
                     lcd_printf("Turn 90 C-Clockwise");
                     //Turn counter-clockwise
                     move_turn_counter_clockwise(sensor_data, 90);
                     //Send string over UART
                     uart_sendStr("\nYou turn C-Clockwise");
                     //Set flag equal to zero
                     uart_event = 0;
                 }

             }
         }
         //End Part 3
         //Free the sensor data
         oi_free(sensor_data);
}
