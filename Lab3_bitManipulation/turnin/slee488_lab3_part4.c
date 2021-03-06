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
	DDRB = 0xFF;PORTB = 0x00;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert your solution below */
	unsigned char upper;
	unsigned char lower;
	
    while (1) {
		upper = (PINA & 0xf0) >> 4;
		lower = PINA & 0x0F;
		
		PORTB = upper;
		PORTC = lower;
		PORTC = PORTC << 4;
    }
    return 1;
}
