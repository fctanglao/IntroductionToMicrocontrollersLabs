/* 
 * File:   voltmeter.c
 * Author: francis
 *
 * Created on July 23, 2024, 4:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * Recreate a voltmeter
 */

#define _XTAL_FREQ 1000000

void __interrupt() adc_sample(void);

volatile long int pot_1; 

int main() {
    // Data pins connected to PORTB
    TRISB = 0;
    
    // Configure analog pins, voltage references, and digital I/O
    ADCON1 = 0x0E;
    TRISAbits.RA0 = 1;
    
    // Select A/D conversion clock
    ADCON2bits.ADCS = 0;
    
    // Select A/D acquisition time
    ADCON2bits.ACQT = 1;
    
    // Select A/D justification
    // Right justified
    ADCON2bits.ADFM = 1;
    
    // Select A/D input channel
    ADCON0bits.CHS = 0;
    
    // Turn on A/D module
    ADCON0bits.ADON = 1;
    
    // Configure A/D interrupt
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;
    RCONbits.IPEN = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    while(1)
    {
        // Start conversion
        ADCON0bits.GO = 1;
        
        // 0x0 is 8 bits
        unsigned char intPart = 0x0; 
        unsigned char tenthsPart = 0x0;

        unsigned char bcd; 
        
        // Saves the last value of ADC interrupt to use
        int pot_val;
        pot_val = pot_1; 
        
        while(pot_val >= 205)
        {
            pot_val = pot_val - 205;
            intPart++;
        }
        
        while(pot_val >= 21)
        {
            pot_val = pot_val - 21;
            tenthsPart++;
        }
        
        // Move the integer left and mask
        intPart = intPart << 4; 
        intPart = intPart & 0xF0;
        
        // Mask tenths integer
        tenthsPart = tenthsPart & 0x0F; 
        
        // Combine into an 8 bit
        bcd = intPart | tenthsPart; 
        
        // Output to PORTB
        PORTB = bcd; 
        
        // Delay so sseg isn't switching too fast
        __delay_ms(2); 

    }
    
    return (EXIT_SUCCESS);
}

void __interrupt() adc_sample(void) {
    if(PIR1bits.ADIF && PIE1bits.ADIE)
    {    
        // Reset the flag
        PIR1bits.ADIF = 0;
        
        // Read A/D result registers
        pot_1 = (ADRESH << 8) | ADRESL;
        
    }
}