/*
*	Name: San Lee
*	Lab Section: 024
	Project name: Lab2_introToAVR
	Partners name [none]: 
	Microcontroller [atmega1284]:
	Clock Frequency [8000000]:
*
*/
#include <stdio.h>
// #include "asf.h"
#include <header/io.h>

int main (void)
{

	printf("Hello World\n");
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0¡¯s
	while(1){
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
	return 1;
}
