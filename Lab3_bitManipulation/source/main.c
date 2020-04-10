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
		level = PORTA & 0x0F;
		if(level <= 2){
			PORTC = PORTC | 0x60;
		}
		if(level > 2 && level <= 4){
			PORTC = PORTC | 0x70;
		}
		if(level > 4 && level <= 6){
			PORTC = PORTC | 0x38;	
		}
		if(level > 6 && level <= 9){
			PORTC = PORTC | 0x3C;	
		}
		if(level > 9 && level <= 12){
			PORTC = PORTC | 0x3E;
		}
		if(level > 12 && level <= 15){
			PORTC = PORTC | 0x3F;
		}

    }
    return 1;
}
