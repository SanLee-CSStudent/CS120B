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
#include "timer.h"
#include "simAVRHeader.h"
#include "stdio.h"
#endif

const double keys[8] = {523.25, 587.33, 659.255, 698.456, 783.991, 880.00, 987.767, 1046.50};
const double beat[4] = {896, 448, 224, 112};
char melody[255];
volatile unsigned char tick = 0x00;
unsigned char i = 0x00;
unsigned char button = 0x00;
enum STATE{Start, Init, Wait, IncKey, IncKeyR, DecKey, DecKeyR, Play, PlayR} states;

void set_PWM(double frequency){
    static double current_frequency;

    if(frequency != current_frequency){
        if(!frequency){
            TCCR3B &= 0x08;
        }
        else{
            TCCR3B |= 0x03;
        }

        if(frequency < 0.954){
            OCR3A = 0xFFFF;
        }
        else if(frequency > 31250){
            OCR3A = 0x0000;
        }
        else{
            OCR3A = (short) (8000000 / (2 * 128 * frequency)) - 1;
        }

        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);

    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

void Tick(){
    switch (states){
        case Start:
            states = Init;
            break;
        
        case Init:
            states = Wait;
            break;

        case Wait:
            if(button){
                states = IncKey;
            }
            else if(button == 0x02){
                states = DecKey;
            }
            else if(button == 0x04){
                states = Play;
            }
            else{
                states = Wait;
            }
            break;

        case IncKey:
            if(button){
                states = IncKey;
            }
            else{
                states = IncKeyR;
            }
            break;

        case IncKeyR:
            states = Wait;
            break;

        case DecKey:
            if(button == 0x02){
                states = DecKey;
            }
            else{
                states = DecKeyR;
            }
            break;

        case DecKeyR:
            states = Wait;
            break;

        case Play:
            if(button == 0x04){
                states = Play;
            }
            else{
                states = PlayR;
            }
            break;

        case PlayR:
            states = PlayR;

            break;
        default:
            break;
    }

    switch (states){
        case Start:

            break;
        
        case Init:

            break;

        case Wait:

            break;

        case IncKey:
            
            break;

        case IncKeyR:
            i++;
            set_PWM(keys[i % 8]);
            break;

        case DecKey:
            
            break;

        case DecKeyR:
            i--;
            set_PWM(keys[i % 8]);
            break;

        case Play:

            break;

        case PlayR:
            tick++;
            if(tick % 8 == 0 && tick < 16){
                set_PWM(keys[0]);
            }
            else if(tick % 8 == 0 && tick < 32){
                set_PWM(keys[4]);
            }
            else if(tick % 8 == 0 && tick < 48){
                set_PWM(keys[5]);
            }
            else{
                set_PWM(keys[4]);
                states = Init;
            }
            break;

        default:
            break;
    }
}

/*void Translate(){
    FILE* sheet;

    while((sheet = fopen("Sheet Music.txt", "r")) != EOF){
        fscanf(sheet, "%s", melody);
    }
    

    printf("%s", melody[0]);
    fclose(sheet);
}*/

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(1);
    TimerOn();
    states = Start;
    PWM_on();
    while (1) {
        button = ~PINA & 0x0F;
        while(!TimerFlag){}
        TimerFlag = 0x00;

        Tick();
        if(button == 0x08){
            set_PWM(0);
        }
    }
    PWM_off();
    return 1;
}
