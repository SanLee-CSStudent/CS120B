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
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;PORTA = 0xFF;
	// DDRB = 0x00;PORTB = 0xFF;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert your solution below */
	unsigned char level;
	
    while (1) {
		level = PINA & 0x0F;
		if(level <= 0x02){
			PORTC = 0x60;
		}
		if(level > 0x02 && level <= 0x04){
			PORTC = 0x70;
		}
		if(level > 0x04 && level <= 0x06){
			PORTC = 0x38;	
		}
		if(level > 0x06 && level <= 0x09){
			PORTC = 0x3C;	
		}
		if(level > 0x09 && level <= 0x0C){
			PORTC = 0x3E;
		}
		if(level > 0x0C && level <= 0x0F){
			PORTC = 0x3F;
		}

    }
    return 1;
}
