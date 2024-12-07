/* 
 * File:   3-bit_addition_c.c
 * Author: francis
 *
 * Created on July 7, 2024, 5:26 PM
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
    ADCON1 = 0xFF;
    
    // PORTA is output (connected to sseg display)
    TRISA = 0x00;
    
    // PORTD is input (connected to switches)
    TRISD = 0xFF;
    
    while(1)
    {
        unsigned char num1 = PORTD & 0x07;
        unsigned char num2 = (PORTD >> 3) & 0x07;
        
        unsigned char sum = num1 + num2;
        
        PORTA = sseg[sum & 0x0F];
    }
    
    return(EXIT_SUCCESS);
}


