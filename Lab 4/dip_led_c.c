/* 
 * File:   dip_led_c.c
 * Author: francis
 *
 * Created on June 30, 2024, 7:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */

#define LEDC PORTCbits.RC0
#define LEDD PORTDbits.RD0
#define SWITCHC PORTCbits.RC1
#define SWITCHD PORTDbits.RD1

int main() {
    // Turn off the ADC
    ADCON1 = 0xff;
    
    // PORTC bit 0 and PORTD bit 0 are outputs
    TRISC0 = 0x00;
    TRISD0 = 0x00;
    
    // PORTC bit 1 and PORTD bit 1 are inputs
    TRISC1 = 0xff;
    TRISD1 = 0xff;
    
    while (1)
    {
        if (SWITCHC == 0 && SWITCHD == 1)
        {
            // 0 = on and 1 = off (cathode connected to pin)
            LEDC = 1;
            LEDD = 0;
        } else if (SWITCHC == 1 && SWITCHD == 0)
        {
            LEDC = 0;
            LEDD = 1;
        } else if (SWITCHC == 0 && SWITCHD == 0)
        {
            LEDC = 1;
            LEDD = 1;
        } else if (SWITCHC == 1 && SWITCHD == 1)
        {
            LEDC = 0;
            LEDD = 0;
        } else
        {
            LEDC = 1;
            LEDD = 1;
        }
    }
    
    return (EXIT_SUCCESS);
}

