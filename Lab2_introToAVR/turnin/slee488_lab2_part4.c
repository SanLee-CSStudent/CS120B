/*	Author: slee488
 *  Partner(s) Name: NA
 *	Lab Section: 024
 *	Assignment: Lab 2  Exercise 2
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
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs --> PINA
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char total;
	unsigned char diff;

	/* Insert your solution below */
    while (1) {
		total = PINA + PINB + PINC;
		diff = PINA - PINC;
		if(total > 140){
			PORTD = 1;
		}
		
		if(diff > 80){
			PORTD = PORTD | 0x02;
		}
		
		PORTD = PORTD | (total << 2);
		
		
    }
    return 1;
}
