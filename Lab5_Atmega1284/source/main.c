/*	Author: lab
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
#endif

unsigned char LED;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    unsigned char level;
    while (1) {
        level = ~PINA & 0x0F;
        if(level == 0x00){
            LED = 0x40;
        }
        if(level > 0x00 && level <= 0x02){
            LED = 0x60;
        }
        if(level > 0x02 && level <= 0x04){
            LED = 0x70;
        }
        if(level > 0x04 && level <= 0x06){
            LED = 0x38;
        }
        if(level > 0x06 && level <= 0x09){
            LED = 0x3C;
        }
        if(level > 0x09 && level <= 0x0C){
            LED = 0x3E;
        }
        if(level > 0x0C && level <= 0x0F){
            LED = 0x3F;
        }

        PORTC = LED;

    }
    return 1;
}
