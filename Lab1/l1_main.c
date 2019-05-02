#include "lcd.h"

/**
 * @file l1_main.c
 *
 * @brief Can print "Hello World" to the cyBot LCD or
 * can call the rotating banner function from lcd.h
 * @author Nicholas Battani, Swechha Ghimire
 * @date 1/24/2019
 */
int main(void)
{
    //Initialize the LCD. This also clears the screen
    lcd_init();

    // Clear the LCD screen and print "Hello, world" on the LCD
    //lcd_printf("Hello, world");

    //Calls the rotating banner function in lcd.h
    lcd_rotatingBanner("Microcontrollers are lots of fun!");

    return 0;
}
