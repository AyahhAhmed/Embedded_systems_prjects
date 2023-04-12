/*
 * push_button.c
 *
 *  Created on: Apr 10, 2023
 *      Author: Aya
 */

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#define DEBOUNCE_DELAY_MS 50 // debounce delay in milliseconds

int main(void) {
    DDRA  |= (1 << 0) | (1 << 1); // set PA0 and PA1 as output
    PORTA |= (1 << 0) | (1 << 1);
    DDRB  &= ~((1 << 0) | (1 << 1) | (1 << 2)); // set PB0, PB1, and PB2 as input
    PORTB |= ((1 << 0) | (1 << 1) | (1 << 2)); // enable pull-up resistors on PB0, PB1, and PB2

    uint8_t switch_state[3] = {0}; // current state of the switches
    uint8_t last_switch_state[3] = {1,1,1}; // last state of the switches

    while (1) {
        // read current state of PB0, PB1, and PB2

        switch_state[0] = (PINB & (1 << 0)) ? 1 : 0 ;
        switch_state[1] = ((PINB & (1 << 1))>>1) ;
        switch_state[2] = ((PINB & (1 << 2))>>2) ;

        if (switch_state[0] != last_switch_state[0])
        {
        	_delay_ms(DEBOUNCE_DELAY_MS);
        	if (switch_state[0] == (PINB & (1 << (0))))
        	{
        		 PORTA ^= (1 << 0);
        		 _delay_ms(300);
        		 PORTA ^= (1 << 0);
        	}
        	last_switch_state[0] = switch_state[0];
        }

        if (switch_state[1] != last_switch_state[1])
        {
                	_delay_ms(DEBOUNCE_DELAY_MS);
                	if (switch_state[1] == (PINB & (1 << (1))))
                	{
                		 PORTA ^= (1 << 1);
                		 _delay_ms(300);
                		 PORTA ^= (1 << 1);
                	}
                	last_switch_state[1] = switch_state[1];
         }

        if (switch_state[2] != last_switch_state[2])
               {
               	_delay_ms(DEBOUNCE_DELAY_MS);
               	if (switch_state[2] == (PINB & (1 << (2))))
               	{
               		PORTA ^= (1 << 0) | (1 << 1);
               		 _delay_ms(300);
               		PORTA ^= ((1 << 0) | (1 << 1));
               	}
               	last_switch_state[2] = switch_state[2];
               }

        // turn off both LEDs if no switches are pressed
       if (switch_state[0] && switch_state[1] && switch_state[2]) {
           PORTA |= ((1 << 0) | (1 << 1));
        }
    }

    return 0;
}
