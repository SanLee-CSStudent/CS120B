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
#endif

#include "io.h"
#include "timer.h"
#include "keypad.h"

typedef struct task{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

enum DISPLAY_STATES {DS_Start, DS_Wait} DS_states;

int Display_Tick(int state){
    switch(state){
        case DS_Start:
            state = DS_Wait;
            break;

        case DS_Wait:
            state = DS_Wait;
            break;

        default:
            break;
    }

    switch(state){
        case DS_Start:
            break;

        case DS_Wait:

            break;

        default:
            break;
    }

    return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below */
    unsigned char input;

    LCD_init();

    LCD_DisplayString(1, "CS12B is Legend... wait for it DARY!");

    static task DS_task;
    DS_task.state = DS_Start;
    DS_task.period = 100;
    DS_task.elapsedTime = DS_task.period;
    DS_task.TickFct = &Display_Tick;

    TimerSet(100);
    TimerOn();

    while (1) {

        if(DS_task.elapsedTime == DS_task.period){
            DS_task.state = DS_task.TickFct(DS_task.state);
            DS_task.elapsedTime = 0;
        }

        DS_task.elapsedTime += 100;

        input = GetKeypadKey();
        switch(input){
            case '\0': PORTB = 0x1F; break;
            case '0': PORTB = 0x00; break;
            case '1': PORTB = 0x01; break;
            case '2': PORTB = 0x02; break;
            case '3': PORTB = 0x03; break;
            case '4': PORTB = 0x04; break;
            case '5': PORTB = 0x05; break;
            case '6': PORTB = 0x06; break;
            case '7': PORTB = 0x07; break;
            case '8': PORTB = 0x08; break;
            case '9': PORTB = 0x09; break;
            case 'A': PORTB = 0x0A; break;
            case 'B': PORTB = 0x0B; break;
            case 'C': PORTB = 0x0C; break;
            case 'D': PORTB = 0x0D; break;
            case '*': PORTB = 0x0E; break;
            case '#': PORTB = 0x0F; break;
            default: PORTB = 0x1B; break;
        }

        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
