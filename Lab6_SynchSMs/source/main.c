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
#include "timer.h"
#endif

enum STATE{Start, ONE, TWO, THREE, FOUR, PRESS, RESUMEPRESS, RESUMERELEASE, RELEASE} states;
unsigned char LEDC = 0x00;
unsigned char button = 0x00;
unsigned char press = 0x00;
unsigned char next = 0x00;

void stayLit(int );

void Tick(){

    switch(states){
        case Start:
            states = ONE;
            break;

        case ONE:
            next = 0x01;
            if(button){
                states= PRESS;
            }
            else{
                states = TWO;
            }
            break;

        case TWO:
            next = 0x02;
            if(button){
                states= PRESS;
            }
            else{
                states = THREE;
            }
            break;

        case THREE:
            next = 0x04;
            if(button){
                states= PRESS;
            }
            else{
                states = FOUR;
            }
            break;
        
        case FOUR:
            next = 0x08;
            if(button){
                states= PRESS;
            }
            else{
                states = ONE;
            }
            break;
        
        case PRESS:
            if(button){
                states = PRESS;
            }
            else {
                states = RELEASE;
            }
            break;

        case RELEASE:
            if(button){
                states = RESUMEPRESS;
            }
            else{
                states = RELEASE;
            }

            break;

        case RESUMEPRESS:
            if(button){
                states = RESUMEPRESS;
            }
            else{
                states = RESUMERELEASE
            }
            break;

        case RESUMERELEASE:
            if(next == 0x01){
                states = TWO;
            }
            else if(next == 0x02){
                states = THREE;
            }
            else if(next == 0x04){
                states = FOUR;
            }
            else{
                states = ONE;
            }
            
            break;

        default:
            break;
    }

    switch(states){
        case Start:
            break;

        case ONE:
            LEDC = 0x01;
            break;

        case TWO:
            LEDC = 0x02;
            break;

        case THREE:
            LEDC = 0x04;
            break;

        case FOUR:
            LEDC = 0x02;
            break;
        
        case RELEASE:
            // stayLit(LEDC);
            break;

        default:
            break;
    }

}

void stayLit(int c){
    LEDC = c;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    states = Start;

    TimerSet(300);
    TimerOn();

    /* Insert your solution below */
    while (1) {
        button = (~PINA) & 0x01;
        Tick();
        PORTC = LEDC;
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
