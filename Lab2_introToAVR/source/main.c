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
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs --> PINA
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char temp;
    unsigned char cntavail;
	unsigned char i;
	/* Insert your solution below */
    while (1) {
		cntavail = 0x00;
		temp = PINA & 0x0F;
		
		for(i=3; i >= 0; i++){
			if(((temp >> i) & 0x00) == 0){
				cntavail = cntavail + 1;
			}
			else{
				cntavail = cntavail;
			}
		}
		
		PORTC = cntavail;
		
    }
    return 1;
}
