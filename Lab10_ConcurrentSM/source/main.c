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
unsigned char frequency = 0x10;
unsigned char button = 0x00;

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

unsigned char threshhold = 0x03;
unsigned char eTick = 0x00;

enum ES_States{eStart, eWait, eON, HIGH, LOW, Inc, Dec} eState;
void ES_tick(){
    switch(eState){
        case eStart:
            eState = eWait;
            break;

        case eWait:
            if(button){
                eState = eON;
                
            }
            else if(button == 0x02){
                eState = Inc;
                
            }
            else if(button == 0x04){
                eState = Dec;
                
            }
            else{
                eState = eWait;
            }
            break;

        case Inc:
            if(button == 0x02){
                eState = Inc;
            }
            else{
                if(threshhold < 8){
                    threshhold++;
                }   
            }
            
            break;

        case Dec:
            if(button == 0x04){
                eState = Dec;
            }
            else{
                if(threshhold > 1){
                    threshhold--;
                }
            }

            break;

        case eON:
            eTick = 0;
            if(button){
                eState = HIGH;
            }
            else{
                eState = eWait;
            }
            break;
        
        case HIGH:
            if(eTick > threshhold){
                if(button){
                    eState = LOW;
                    eTick = 0;
                }
                else{
                    eState = eWait;
                }
            }
            break;

        case LOW:
            if(eTick > threshhold){
                if(button){
                    eTick = 0;
                    eState = HIGH;
                }
                else{
                    eState = eWait;
                }
            }
            break;

        default:

            break;
    }

    switch(eState){
        case eStart:
            PORTB = 0x00;
            break;

        case eWait:
            
            break;

        case eON:
                       
            break;

        case HIGH:
            frequency = 0x10;
            PORTB = frequency;
            eTick++;
            break;

        case LOW:
            frequency = 0x00;
            PORTB = frequency;
            eTick++;
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
    TimerSet(1);
    TimerOn();

    unsigned long TL_elapsedTime = 0;
    unsigned long BS_elapsedTime = 0;
    const unsigned long period = 1;

    tState = TL_Start;
    bState = BS_Start;
    cState = Start;
    eState = eStart;
    while (1) {
        button = (~PINA) & 0x07;
        

        if(BS_elapsedTime >= 1000){
            BS_tick();
            BS_elapsedTime = 0;
        }

        if(TL_elapsedTime >= 300){
            TL_tick();
            CL_tick();
            TL_elapsedTime = 0;
        }

        ES_tick();
        
        while(!TimerFlag){}
        TimerFlag = 0;
        TL_elapsedTime += period;
        BS_elapsedTime += period;
    }
    return 1;
}
