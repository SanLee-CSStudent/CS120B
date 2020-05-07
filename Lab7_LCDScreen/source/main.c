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
#include "io.h"
#endif

enum STATE{Start, Init, Inc, Dec, IncR, DecR, IncP, DecP, ResetR, Reset} state;
unsigned char button = 0x00;
unsigned char count = 0x00;

void Tick(){
	
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(button == 0x01){
				state = Inc;
			}
			else if(button == 0x02){
				state = Dec;
			}
			else if(button == 0x03){
				state = Reset;
			}
			else {
				state = Init;
			}

			break;
		case Inc:
			// unsigned char tempA = (PINA & 0x01);
            if(button == 0x01){
                state = Inc;
                // pressing = 0x01;
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
			    state = IncR;
            }
			
			break;
		
		case IncR:
			state = Init;
			
			break;

		case Dec:
			// unsigned char tempB = (PINA & 0x02);
			if(button == 0x02){
				state = Dec;
			}
            if(button == 0x03){
                state = Reset;
            }
			else{
				state = DecR;
			}
			break;

		case DecR:
			state = Init;
			
			break;

        case Reset:
            if(button == 0x03){
                state = Reset;
            }
            else{
                state = ResetR;
            }
            break;

		case ResetR:
			state = Init;
			break;
			
		default:
			break;
	}
	
	switch(state){
		case Start:
			count = 0x00;
		break;
		case Init:

		break;

		case Inc:
	
			
			break;

		case IncR:
			if(PORTC < 9){
				count++;
			}
			LCD_WriteData(count + '0');
			break;
		
		case Dec:

			
			break;

		case DecR:
			if(PORTC > 0){
				count--;
			}
			LCD_WriteData(count + '0');
			break;

		case ResetR:
			count = 0x00;
            LCD_WriteData(count + '0');
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
    LCD_init();

    while (1) {
		button = ~PINA & 0x03;
		Tick();
    }
    return 1;
}
