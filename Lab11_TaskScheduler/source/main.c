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
#include "io.h"
#include "timer.h"
#include "keypad.h"
#endif

#include <avr/interrupt.h>

typedef struct task{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

enum DISPLAY_STATES {DS_Start, DS_Wait} DS_states;

int DS_Tick(int state){
    static unsigned char i = 0x00;

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
            // LCD_ClearScreen();
            if(i == 0){
                LCD_ClearScreen();
            }
            else if(i == 1){LCD_DisplayString(16, "C");}
            else if(i == 2){LCD_DisplayString(15, "CS");}
            else if(i == 3){LCD_DisplayString(14, "CS1");}
            else if(i == 4){LCD_DisplayString(13, "CS12");}
            else if(i == 5){LCD_DisplayString(12, "CS120");}
            else if(i == 6){LCD_DisplayString(11, "CS120B");}
            else if(i == 7){LCD_DisplayString(10, "CS120B ");}
            else if(i == 8){LCD_DisplayString(9, "CS120B i");}
            else if(i == 9){LCD_DisplayString(8, "CS120B is");}
            else if(i == 10){LCD_DisplayString(7, "CS120B is ");}
            else if(i == 11){LCD_DisplayString(6, "CS120B is L");}
            else if(i == 12){LCD_DisplayString(5, "CS120B is Le");}
            else if(i == 13){LCD_DisplayString(4, "CS120B is Leg");}
            else if(i == 14){LCD_DisplayString(3, "CS120B is Lege");}
            else if(i == 15){LCD_DisplayString(2, "CS120B is Legen");}
            else if(i == 16){LCD_DisplayString(1, "CS120B is Legend");}
            else if(i == 17){LCD_DisplayString(1, "S120B is Legend.");}
            else if(i == 18){LCD_DisplayString(1, "120B is Legend..");}
            else if(i == 19){LCD_DisplayString(1, "20B is Legend...");}
            else if(i == 20){LCD_DisplayString(1, "0B is Legend...w");}
            else if(i == 21){LCD_DisplayString(1, "B is Legend...wa");}
            else if(i == 22){LCD_DisplayString(1, " is Legend...wai");}
            else if(i == 23){LCD_DisplayString(1, "is Legend...wait");}
            else if(i == 24){LCD_DisplayString(1, "s Legend...wait ");}
            else if(i == 25){LCD_DisplayString(1, " Legend...wait f");}
            else if(i == 26){LCD_DisplayString(1, "Legend...wait fo");}
            else if(i == 27){LCD_DisplayString(1, "egend...wait for");}
            else if(i == 28){LCD_DisplayString(1, "gend...wait for ");}
            else if(i == 29){LCD_DisplayString(1, "end...wait for i");}
            else if(i == 30){LCD_DisplayString(1, "nd...wait for it");}
            else if(i == 31){LCD_DisplayString(1, "d...wait for it ");}
            else if(i == 32){LCD_DisplayString(1, "...wait for it D");}
            else if(i == 33){LCD_DisplayString(1, "..wait for it DA");}
            else if(i == 34){LCD_DisplayString(1, ".wait for it DAR");}
            else if(i == 35){LCD_DisplayString(1, "wait for it DARY");}
            else if(i == 36){LCD_DisplayString(1, "ait for it DARY!");}
            else if(i == 37){LCD_DisplayString(1, "it for it DARY!");}
            else if(i == 38){LCD_DisplayString(1, "t for it DARY!");}
            else if(i == 39){LCD_DisplayString(1, " for it DARY!");}
            else if(i == 40){LCD_DisplayString(1, "for it DARY!");}
            else if(i == 41){LCD_DisplayString(1, "or it DARY!");}
            else if(i == 42){LCD_DisplayString(1, "r it DARY!");}
            else if(i == 43){LCD_DisplayString(1, " it DARY!");}
            else if(i == 44){LCD_DisplayString(1, "it DARY!");}
            else if(i == 45){LCD_DisplayString(1, "t DARY!");}
            else if(i == 46){LCD_DisplayString(1, " DARY!");}
            else if(i == 47){LCD_DisplayString(1, "DARY!");}
            else if(i == 48){LCD_DisplayString(1, "ARY!");}
            else if(i == 49){LCD_DisplayString(1, "RY!");}
            else if(i == 50){LCD_DisplayString(1, "Y!");}
            else if(i == 51){LCD_DisplayString(1, "!");}
            else if(i == 52){LCD_DisplayString(1, "");}
            else{
                i = 0;
            }

            i++;
            break;

        default:
            break;
    }

    return state;
}

enum KEYPAD_STATE{KS_Start, KS_Wait} KS_states;

int KS_Tick(int state){
    switch(state){
        case KS_Start:
            state = KS_Wait;
            break;

        case KS_Wait:
            state = KS_Wait;
            break;
        
        default:

            break;
    }

    switch(state){
        case KS_Start:

            break;

        case KS_Wait:
            input = GetKeypadKey();

            switch(input){
                // case '\0': LCD_DisplayString(1, ""); break;
                case '0': LCD_DisplayString(1, "0"); break;
                case '1': LCD_DisplayString(1, "1"); break;
                case '2': LCD_DisplayString(1, "2"); break;
                case '3': LCD_DisplayString(1, "3"); break;
                case '4': LCD_DisplayString(1, "4"); break;
                case '5': LCD_DisplayString(1, "5"); break;
                case '6': LCD_DisplayString(1, "6"); break;
                case '7': LCD_DisplayString(1, "7"); break;
                case '8': LCD_DisplayString(1, "8"); break;
                case '9': LCD_DisplayString(1, "9"); break;
                case 'A': LCD_DisplayString(1, "A"); break;
                case 'B': LCD_DisplayString(1, "B"); break;
                case 'C': LCD_DisplayString(1, "C"); break;
                case 'D': LCD_DisplayString(1, "D"); break;
                case '*': LCD_DisplayString(1, "*"); break;
                case '#': LCD_DisplayString(1, "#"); break;
                default: break;
            }
            break;
        
        default:

            break;
    }

    return state;
}

unsigned char input;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    LCD_init();
    LCD_ClearScreen();

    static task DS_task;
    DS_task.state = DS_Start;
    DS_task.period = 200;
    DS_task.elapsedTime = DS_task.period;
    DS_task.TickFct = &DS_Tick;

    static task KS_task;
    KS_task.state = KS_Start;
    KS_task.period = 200;
    KS_task.elapsedTime = KS_task.period;
    KS_task.TickFct = &KS_Tick;

    TimerSet(200);
    TimerOn();

    while (1) {

        if(DS_task.elapsedTime == DS_task.period){
            // DS_task.state = DS_task.TickFct(DS_task.state);
            DS_task.elapsedTime = 0;
        }

        if(KS_task.elapsedTime == KS_task.period){
            KS_task.state = DS_task.TickFct(DS_task.state);
            KS_task.elapsedTime = 0;
        }

        while(!TimerFlag);
        TimerFlag = 0;

        DS_task.elapsedTime += 200;
        KS_task.elapsedTime += 200;
    }
    return 1;
}
