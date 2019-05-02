/*
 * scan.c
 *
 *  Created on: Apr 4, 2019
 *      Author: battani
 */

#include "scan.h"


//String that we use to print to putty
char sendstr[40]="";

//Struct that will hold our bonus meme readings
float ping_Readings[181];
float adc_Readings[181];
//float ping_Object[181][181];
//float adc_Object[181][181];

int found_object_one_starting = 0;
int found_object_one_ending = 0;

int found_object_two_starting = 0;
int found_object_two_ending = 0;

int found_object_three_starting = 0;
int found_object_three_ending = 0;

float getDistance(int d){
   return (99564 *pow(d,-1.158));
}
struct objects {
    int starting_degree;
    int ending_degree;
    int angle;
    int distance;
    int width;
};
void full_scan(){

    servo_move(0);

    int degrees = 0;
    for(degrees = 0; degrees <= 180; degrees++){
        timer_waitMillis(100);
        float adc_Value = adc_read();
        float adc_Distance = getDistance(adc_Value);

        float ping_Distance = ping_read();

        adc_Readings[degrees] = adc_Distance;
        ping_Readings[degrees] = ping_Distance;
        servo_move(degrees);
    }

}

void print_UART(){
    //Print the header
    sprintf(sendstr, "%-20s%-20s%-20s\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance(cm)");
    //Send it to UART and PUTTY
    uart_sendStr(sendstr);

    int i = 0;

    for(i = 0; i<=180; i = i+2){
        //Add all the data
        sprintf(sendstr, "%-20d%-20f%-20f\r\n",i,adc_Readings[i],ping_Readings[i]);
        //Send the string over UART and PUTTY
        uart_sendStr(sendstr);
    }
}


void find_smallest(){
    int i = 0;

    int num_objects = 0;
    int object_found = 0;


    struct objects found[10];

    for(i = 0; i<=180; i = i + 2){

            if(object_found == 0 && adc_Readings[i]<50 && ping_Readings[i]<50){
                found[num_objects].starting_degree = i;
                object_found = 1;

            }
            if(object_found == 1 && adc_Readings[i]>50){
                found[num_objects].ending_degree = i;
                object_found = 0;
                num_objects++;
            }
    }

    for(i = 0; i<num_objects; i++){
        int angle;
        int offset;
        angle = found[i].ending_degree- found[i].starting_degree;
        if(angle >15 && angle<180){
        offset = found[i].ending_degree-(angle/2);
        found[i].angle = angle;
        found[i].distance = ping_Readings[offset];
        found[i].width = 2 * (found[i].distance * (tan((found[i].angle)*(M_PI/180))));

        }
    }
    int smallest_angle = found[0].angle;
    int turn_to_angle = 0;
    for(i = 0; i<num_objects; i++){
        if(found[i].angle<smallest_angle){
            smallest_angle = found[i].angle;
            turn_to_angle = found[i].starting_degree;
        }
    }
    servo_move(turn_to_angle);

    printf("Object 1 width: %d\n Object 1 starting angle: %d\n Object 1 ending angle: %d\n Object 1 angle: %d\n Object 1 distance: %d\n  Object 2 width: %d\n Object 2 angle: %d\n Object 2 distance: %d\n Object 3 Width: %d\n Object 3 angle: %d\n Object 3 distance : %d\n",found[0].width,found[0].starting_degree,found[0].ending_degree,found[0].angle,found[0].distance,found[1].width,found[1].angle,found[1].distance,found[2].width,found[2].angle,found[2].distance);
    lcd_printf("Objects found: %d",num_objects);


}


