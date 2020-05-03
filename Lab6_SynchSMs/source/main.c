/*	Author: slee488
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF; PORTC = 0x00;
    TimerSet(1000);
    TimerOn();
    unsigned char tmpC = 0x00;

    /* Insert your solution below */
    while (1) {
        tmpC = ~tmpC;
        PORTC = tmpB;
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
