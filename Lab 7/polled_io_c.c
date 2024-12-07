/* 
 * File:   polled_io_c.c
 * Author: francis
 *
 * Created on July 15, 2024, 7:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */

#define POT PORTBbits.RB1
#define LED PORTDbits.RD1

int main() {
    // Turn off ADC
    ADCON1 = 0xFF;
    
    // PORTD is output (connected LED)
    TRISD = 0x00;
    
    // PORTB is input (connected to edge triggered )
    TRISB = 0xFF;
    
    while (1)
    {
        // Sets LED to the value of POT (0V to 5V)
        LED = POT;
    }
    
    return (EXIT_SUCCESS);
}

