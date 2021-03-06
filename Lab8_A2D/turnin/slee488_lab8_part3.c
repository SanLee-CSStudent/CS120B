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

unsigned short input;
unsigned short max = 0x00C3;
unsigned char upper;
unsigned char lower;

void ADC_init(){    
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    ADC_init();
    while (1) {
        input = ADC;
        if(input >= (max/2)){
            lower = (char) input;
            upper = (char) (input >> 8);

            PORTC = lower;
            PORTD = upper;
        }
        else{
            PORTC = 0x00;
            PORTD = 0x00;
        }
        
    }
    return 1;
}
