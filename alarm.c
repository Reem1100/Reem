#include <stdio.h>

#include "ifttt.h"

#include <wiringPi.h>

#include <curl/curl.h>

int main(int argc, char *argv[])

{

        extern int ifttt(char* , char* , char* , char* );       

        int val;

        int state;

        int change_delay;

        wiringPiSetup () ;

        pinMode(0, INPUT);

        pinMode(1, OUTPUT); 

        pinMode(2, OUTPUT);

        

        state = 0; /*state 0 - inactive, state 1 - armed, state -1 triggered

        */

        change_delay = 0;

	 #define ARMED_LED 2

	 #define ALARM_LED 1

        while(1) {

                if (state == 0) {

                        digitalWrite(ARMED_LED, LOW);

                        digitalWrite(ALARM_LED, LOW);

                } else if (state == 1) {

                        digitalWrite(ARMED_LED, HIGH);

                        digitalWrite(ALARM_LED, LOW);

                } else if (state == -1) {

			printf("Waiting for reset\n");

                        digitalWrite(ALARM_LED, HIGH);

                }



                if (change_delay > 0) {

                        delay(change_delay);

                }

                val = digitalRead(0);

                if (val == 1) {

			ifttt("http://red.eecs.yorku.ca:8080/trigger/event/with$

                        if (state >= 0) {

                                change_delay = 500;

                        }

                        state = -1;

                        printf("Alarm\n");

                } else {

                        if (state <= 0) {

                                change_delay = 250;

                        }

                        state = 1;

		
			printf("Armed\n");

                }



                delay(100);

        }

        /*NOTREACHED*/

        return 0 ;

}
