/*	Author: lab
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
#include "timer.h"
#endif

unsigned char TLED = 0x00;
unsigned char BLED = 0x00;

enum TL_States {TL_Start, ONE, TWO, THREE} tState;
void TL_tick(){
    switch(tState){
        case TL_Start:
            tState = ONE;
            break;
        
        case ONE:
            tState = TWO;
            break;

        case TWO:
            tState = THREE;
            break;
        
        case THREE:
            tState = ONE;
        
        default:
            break;
    }

    switch(tState){
        case TL_Start:
            TLED = 0x00;
            break;
        
        case ONE:
            TLED = 0x01;
            break;

        case TWO:
            TLED = 0x02;
            break;
        
        case THREE:
            TLED = 0x04;
        
        default:
            break;
    }
}

enum BS_States {BS_Start, BLINK, OFF} bState;
void BS_tick(){
    switch(bState){
        case BS_Start:
            bState = BLINK;
            break;
        
        case BLINK:
            bState = OFF;
            break;

        case OFF:
            bState = BLINK;
            break;

        default:
            break;
    }

    switch(bState){
        case BS_Start:
            BLED = 0x00;
            break;
        
        case BLINK:
            BLED = 0x08;
            break;

        case OFF:
            BLED = 0x00;
            break;

        default:
            break;
    }
}

enum CL_States{Start, Combine} cState;
void CL_tick(){
    switch(cState){
        case Start:
            cState = Combine;
            break;

        case Combine:
            cState = Combine;
            break;

        default:
            break;
    }

    switch(cState){
        case Start:
            break;

        case Combine:
            PORTC = TLED | BLED;
            break;

        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    TimerSet(100);
    TimerOn();

    unsigned long TL_elapsedTime = 0;
    unsigned long BS_elapsedTime = 0;
    const unsigned long period = 100;

    tState = TL_Start;
    bState = BS_Start;
    cState = Start;
    while (1) {
        if(TL_elapsedTime >= 300){
            TL_tick();
            TL_elapsedTime = 0;
        }

        if(BS_elapsedTime >= 1000){
            BS_tick();
            BS_elapsedTime = 0;
        }

        CL_tick();

        while(!TimerFlag){}
        TimerFlag = 0;
        TL_elapsedTime += period;
        BS_elapsedTime += period;
    }
    return 1;
}
