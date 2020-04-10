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
	unsigned char tempA;
	unsigned char tempC;
    unsigned char cntavail;
	unsigned char i;
	/* Insert your solution below */
    while (1) {
		cntavail = 0x00;
		tempA = PINA & 0x0F;
		
		for(i = 3; i >= 0; i--){
			tempC = (tempA >> i) & 0x01;
			/*if(tempC == 0x01){
				cntavail = cntavail;
			}
			else{
				cntavail = cntavail + 1;
			}*/
		}
		
		PORTC = cntavail;
		
    }
    return 1;
}
