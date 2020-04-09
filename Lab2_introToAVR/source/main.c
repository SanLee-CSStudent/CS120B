/*	Author: slee488
 *  Partner(s) Name: NA
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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs --> PINA
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    while (1) {
		
		if((PINA & 0x03) == 0x01){
			PORTB = 0x01;
		}
		else{
			PORTB = 0x00;
		}
    }
    return 1;
}
