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
	DDRB = 0x00;PORTB = 0xFF;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert your solution below */
	unsigned char cnt = 0;
	unsigned tempA;
	char j;
	
    while (1) {
		cnt = 0x00;
		
		for(j = 0; j < 8; j++){
			tempA = (PINA >> j) & 0x01;
			if(tempA == 1){
				cnt = cnt + 1;
			}
			
			tempA = (PINB >> j) & 0x01;
			if(tempA == 1){
				cnt = cnt + 1;
			}
		}
		
		PORTC = cnt;
		
    }
    return 1;
}
