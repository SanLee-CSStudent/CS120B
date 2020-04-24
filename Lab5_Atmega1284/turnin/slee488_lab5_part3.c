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

enum STATE{Start, Init, stage0, stage1, stage2, stage3, stage4, stage5, r0, r1, r2, r3, r4, r5, r6} state;

void Tick(){
	
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
            if(PINA == 0x01){
                state = r0;
            }
			break;

        case r0:
            if(PINA == 0x00){
                state = stage0;
            }
            else{
                state = r0;
            }
            break;

		case stage0:
            if(PINA == 0x01){
                state = r1;
            }
            else{
                state = stage0;
            }
			break;

        case r1:
            if(PINA == 0x00){
                state = stage1;
            }
            else{
                state = r1;
            }
            break;

        case stage1:
            if(PINA == 0x01){
                state = r2;
            }
            else{
                state = stage1;
            }
			break;

        case r2:
            if(PINA == 0x00){
                state = stage2;
            }
            else{
                state = r2;
            }
            break;

        case stage2:
            if(PINA == 0x01){
                state = r3;
            }
            else{
                state = stage2;
            }
			break;

        case r3:
            if(PINA == 0x00){
                state = stage3;
            }
            else{
                state = r3;
            }
            break;

        case stage3:
            if(PINA == 0x01){
                state = r4;
            }
            else{
                state = stage3;
            }
			break;

        case r4:
            if(PINA == 0x00){
                state = stage4;
            }
            else{
                state = r4;
            }
            break;

        case stage4:
            if(PINA == 0x01){
                state = r5;
            }
            else{
                state = stage4;
            }
			break;

        case r5:
            if(PINA == 0x00){
                state = stage5;
            }
            else{
                state = r5;
            }
            break;

        case stage5:
            if(PINA == 0x01){
                state = r6;
            }
            else{
                state = stage5;
            }
			break;

        case r6:
            if(PINA == 0x00){
                state = Init;
            }
            else{
                state = r6;
            }
            break;
		default:
			break;
	}
	
	switch(state){
		case Start:
			PORTC = 0x00;
			break;
		case Init:
            PORTC = 0x00;
			break;
		case stage0:
            PORTC = PORTC | 0x01;
			break;
        case stage1:
            PORTC = PORTC | 0x04;
			break;
        case stage2:
            PORTC = PORTC | 0x10;
			break;
        case stage3:
            PORTC = PORTC | 0x02;
			break;
        case stage4:
            PORTC = PORTC | 0x08;
			break;
        case stage5:
            PORTC = PORTC | 0x20;
			break;
		default:
			break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert DDR and PORT initializations */
	state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
    }
    return 1;
}
