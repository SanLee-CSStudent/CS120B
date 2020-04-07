/**
 * \file
 *
 * \brief Empty user application template
 *
	Project name: Lab2_introToAVR
	Partners name [none]: Jo Smith
	Microcontroller [atmega1284]:
	 Clock Frequency [8000000]:
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "header/io.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	/* Insert application code here, after the board has been initialized. */
	printf("Hello World\n");
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0¡¯s
	while(1){
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
	return 1;
}
