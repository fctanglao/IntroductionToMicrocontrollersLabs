/* 
 * File:   dip_sseg_c.c
 * Author: francis
 *
 * Created on July 1, 2024, 2:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */

int main() {
    char sseg[16] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84, 0x88, 0xE0, 0xB1, 0xC2, 0xB0, 0xB8};
    
    // Turn off ADC
    ADCON1 = 0xff;
    
    // PORTA is output (connected to sseg display)
    TRISA = 0x00;
    
    // PORTB is input (connected to switches)
    TRISB = 0xff;
    
    while (1)
    {
        PORTA = sseg[PORTB & 0x0F];
    }
    
    return (EXIT_SUCCESS);
}

