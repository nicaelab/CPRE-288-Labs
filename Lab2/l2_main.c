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
#include "open_interface.h"
#include "movement.h"

//Global integer to store value of left wheel
int left_wheel = 380;
//Global integer to store value of right wheel
int right_wheel = 380;

int main(void)
{
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    // Part 1
//    move_forward(sensor_data, 1000, left_wheel, right_wheel, 0);
    // End Part 1

    // Part 2
//    move_forward(sensor_data, 500, left_wheel, right_wheel, 0);
//    move_turn_clockwise(sensor_data, 90);
//    move_forward(sensor_data, 500, left_wheel, right_wheel, 0);
//    move_turn_clockwise(sensor_data, 90);
//    move_forward(sensor_data, 500, left_wheel, right_wheel, 0);
//    move_turn_clockwise(sensor_data, 90);
//    move_forward(sensor_data, 500, left_wheel, right_wheel, 0);
    // End Part 2

    // Part 3
     move_forward(sensor_data, 2000, left_wheel, right_wheel, 1);
    // End Part 3

    oi_free(sensor_data);

    return 0;
}
