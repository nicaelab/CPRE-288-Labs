/*
 * cliff.c
 *
 *  Created on: Apr 18, 2019
 *      Author: ehbrandt
 */


#include "cliff.h"


//we can now input a distance for the roomba to move. This way, we can move, scan for objects, move, scan, etc, and it still stops at the tape and hole
//maybe return int instead of void? 0 if nothing was found, 1 if the hole was found, and 2 if the tape was found? we can then call things based on what is returned
//I also added another if so that if it hits an object it backs up and stops.
void move_cliff(oi_t* sensor, int millimeters)
{
       oi_setWheels(100, 100);      //wheels move forward at slow speed
       int cliff = 0;
       //1 if cliff detected (based on cliffFrontRight etc)
       int front_right_cliff = 0;
       int front_left_cliff = 0;
       int right_cliff = 0;
       int left_cliff = 0;
       int rightBumper = 0;      //0 if the right bumper is not activated, 1 if the right bumper bumps something
       int leftBumper = 0;       //0 if the left bumper is not activated, 1 if the left bumper bumpts something
       int sum = 0;
       while(sum < millimeters)    //roomba keeps moving until it reaches the desired distance
       {
//           oi_setWheels(500, 500);

            oi_update(sensor);
            sum += sensor -> distance;
            //updates variables depening on if cliff detected
            front_right_cliff += sensor->cliffFrontRight;
            front_left_cliff += sensor->cliffFrontLeft;
            left_cliff += sensor->cliffLeft;
            right_cliff += sensor->cliffRight;
            rightBumper += sensor -> bumpRight;
            leftBumper += sensor -> bumpLeft;

//            lcd_printf("%d", sensor->cliffRightSignal);     //print light sensor value; roomba 13: if above 2700 tape found, if 2500 on regular ground, if dropped low hole

            //I think wee need a break in here or to set cliff = 1 in here. Without them, i think the roomba is actually stuck in this while loop because we never tell it to move
            //again
            if(sensor->cliffFrontRightSignal >= 2700 || sensor->cliffFrontLeftSignal >= 2700 || sensor->cliffRightSignal >= 2700 || sensor->cliffLeftSignal >= 2700)     //detected tape
            {
                oi_setWheels(0, 0);
                lcd_printf("LS: %d\nFLS: %d\nFRS: %d\nRS: %d", sensor->cliffLeftSignal, sensor->cliffFrontLeftSignal, sensor->cliffFrontRightSignal);
                break;
                //notify user: tape detected on right or left side
                //autonomous movement function to find corner
            }

            if (front_right_cliff == 1 || front_left_cliff == 1 || left_cliff == 1 || right_cliff == 1)
            {
                oi_setWheels(0, 0);
                cliff = 1;
                //notify user: hole detected from which sensor
                //back up 10 cm
                move_backward(sensor,10);
//              lcd_printf("%d", sensor->cliffFrontRightSignal);
                parallel_to_tape(sensor);
            }


            //if the right or left bumper get hit, the roomba backs up and stops.
            if(rightBumper == 1 || leftBumper == 1)
            {
                move_backward(sensor, 150);
                sum = sum - 150;
            }


            rightBumper = 0;
            leftBumper = 0;



        if (cliff)
        {
            front_right_cliff = 0;
            front_left_cliff = 0;
            left_cliff = 0;

            right_cliff = 0;
            break;
        }


    }
       //oi_setWheels(0, 0); //stop

}

//the Roomba turns slightly too far. Since it is turning right, the left sensor sees the tape for too long, but if we ignore the left sensor, it doesn't turn enough.
//However, if we ignore the left sensor, I think this works as long as we repeatedly call move_cliff and parallel_to_tape. The roomba moves, finds tape turns, then moves a little
//hits the tape again, turns a little, moves, turns, moves, turns, so that might work. But, repeatedly calling these functions was a little weird.
void parallel_to_tape(oi_t* sensor)     //turn a few degrees on each loop until running parallel to tape
{
    //while any of the sensors see the tape, keep turning right a little bit
    while(sensor->cliffFrontRightSignal >= 2700 || sensor->cliffFrontLeftSignal >= 2700 || sensor->cliffRightSignal >= 2700 || sensor->cliffLeftSignal >= 2700)
    {
        lcd_printf("LS: %d\nFLS: %d\nFRS: %d\nRS: %d", sensor->cliffLeftSignal, sensor->cliffFrontLeftSignal, sensor->cliffFrontRightSignal, sensor->cliffRightSignal);
        turn_right(sensor, -5);
    }
}



//while(sum < millimeters)    //roomba keeps moving until it reaches the desired distance
//       {
////           oi_setWheels(500, 500);
//        while (!cliff) //keep moving forward while the roomba doesn't bump into anything
//        {
//            oi_update(sensor);
//            sum += sensor -> distance;
//            //updates variables depening on if cliff detected
//            front_right_cliff += sensor->cliffFrontRight;
//            front_left_cliff += sensor->cliffFrontLeft;
//            left_cliff += sensor->cliffLeft;
//            right_cliff += sensor->cliffRight;
//
////            lcd_printf("%d", sensor->cliffRightSignal);     //print light sensor value; roomba 13: if above 2700 tape found, if 2500 on regular ground, if dropped low hole
//
//            if(sensor->cliffFrontRightSignal >= 2700 || sensor->cliffFrontLeftSignal >= 2700 || sensor->cliffRightSignal >= 2700 || sensor->cliffLeftSignal >= 2700)     //detected tape
//            {
//                oi_setWheels(0, 0);
//                lcd_printf("LS: %d\nFLS: %d\nFRS: %d\nRS: %d", sensor->cliffLeftSignal, sensor->cliffFrontLeftSignal, sensor->cliffFrontRightSignal);
//                //notify user: tape detected on right or left side
//                //autonomous movement function to find corner
//            }
//
//            if (front_right_cliff == 1 || front_left_cliff == 1 || left_cliff == 1 || right_cliff == 1)
//            {
//                oi_setWheels(0, 0);
//                cliff = 1;
//                //notify user: hole detected from which sensor
//                //back up 10 cm
//                move_backward(sensor,10);
////              lcd_printf("%d", sensor->cliffFrontRightSignal);
//            }
//
//
//        }
//        if (cliff)
//        {
//            front_right_cliff = 0;
//            front_left_cliff = 0;
//            left_cliff = 0;
//
//            right_cliff = 0;
//            break;
//        }
//
//
//    }


