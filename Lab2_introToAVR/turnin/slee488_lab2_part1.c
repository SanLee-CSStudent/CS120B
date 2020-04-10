/*	Partner(s) Name & E-mail:
 *	Lab Section: 024
 *	Assignment: Lab 2  Exercise 1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template 
 * 	or example code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs --> PINA
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    unsigned char tempA;
	/* Insert your solution below */
    while (1) {

		tempA = PINA & 0x03;
	
		if((tempA) == 0x01){
			PORTB = 0x01;
		}
		else{
			PORTB = 0x00;
		}
    }
    return 1;
}
