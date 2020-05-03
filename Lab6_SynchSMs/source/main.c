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

enum STATE{Start, ONE, TWO, THREE} states;
unsigned LEDC = 0x00;

void Tick(){

    switch(states){
        case Start:
            states = ONE;
            break;

        case ONE:
            states = TWO;
            break;

        case TWO:
            states = THREE;
            break;

        case THREE:
            states = ONE;
            break;
        
        default:
            states = ONE;
            break;
    }

    switch(states){
        case Start:
            break;

        case ONE:
            LEDC = 0x01;
            break;

        case TWO:
            LEDC = 0x02;
            break;

        case THREE:
            LEDC = 0x04;
            break;
        
        default:
            states = ONE;
            break;
    }

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF; PORTC = 0x00;

    states = Start;

    TimerSet(1000);
    TimerOn();

    /* Insert your solution below */
    while (1) {
        Tick();
        PORTC = LEDC;
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
