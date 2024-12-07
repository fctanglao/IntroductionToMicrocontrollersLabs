/* 
 * File:   interrupt_io_c.c
 * Author: francis
 *
 * Created on July 16, 2024, 4:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */

#define POT PORTBbits.RB1
#define LED PORTDbits.RD1

void __interrupt() toggleLED (void);

int main() {
    // Turn off ADC
    ADCON1 = 0xFF;
    
    // PORTD is output (connected LED)
    TRISD = 0x00;
    
    // PORTB is input (connected to edge triggered )
    TRISB = 0xFF;
    
    // Setup all interrupts
    INTCON3bits.INT1IE = 1; // Enable INT1
    INTCON3bits.INT1IF = 0; // Reset INT1 flag
    INTCONbits.GIE = 1; // Global interrupt enable

    return (EXIT_SUCCESS);
}

void __interrupt() toggleLED(void)
{
    // Checks which interrupt called the routine
    // Good habit according to prof
    if (INTCON3bits.INT1IE && INTCON3bits.INT1F)
    {
        // Turn off the interrupt flag to avoid recursive interrupt calls
        INTCON3bits.INT1F = 0;
        
        // Sets LED to the value of POT (0V to 5V)
        LED = POT;
    }
}

