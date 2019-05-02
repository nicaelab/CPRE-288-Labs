/**
 * @file l2_main.c
 *
 * @brief Moves the iRobot forward (Part 1), in a square (Part 2),
 * and detects bumps (Part 3)
 *
 * @author Nicholas Battani, Swechha Ghimire
 *
 * @date 2/07/2019
 */

#include "lcd.h"
#include "button.h"

volatile int button_event = 0; // Boolean to keep track of whether a hardware event has happened (button pressed)
volatile int button_num = 0; // keeps track of button pressed


/**
 * main.c
 * Prints the button that has been pressed
 */
void main(void) {
   // #warning "Unimplemented function: int main(void)" // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed


    lcd_init();
    button_init();
    init_button_interrupts(&button_event,&button_num);
//Part 3
    while(1){
        //lcd_printf("%d",button_num);
        if(button_event==1){
            lcd_printf("%d",button_num);
            button_event=0;
        }else{
            lcd_printf("%d",button_num);
        }
    }
//End Part 3
//Part 1
//    while(1){
//        uint8_t button = button_getButton();
//        lcd_printf("Button %d pressed",button);
//    }
//End Part 1


}
