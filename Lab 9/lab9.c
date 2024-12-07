#include <stdio.h>
#include <stdlib.h>
#include "config.h"


/*
 * 
 */

#define _XTAL_FREQ 1000000
void __interrupt() adc_sample(void);

volatile long int pot_1; 




int main() {

    
    // Data pins connected to PORTB
    TRISB = 0x00;
    

    
    // 1 - Configure the A/D Module

    // * Configure analog pins, voltage reference and digital I/O 
    // Reference voltages are VSS and VDD
    ADCON1 = 0x0E;
    TRISAbits.RA0 = 1;
    
    // * Select A/D acquisition time
    // * Select A/D conversion clock
    // Right justified, ACQT = 2 TAD, ADCS = FOSC/2
    ADCON2bits.ADCS = 0; // FOSC/2
    ADCON2bits.ACQT = 1; // ACQT = 2 TAD
    ADCON2bits.ADFM = 1; // Right justified
    
    // * Select A/D input channel
    ADCON0bits.CHS = 0; // Channel 0 (AN0), starting with the potentiometer

    // * Turn on A/D module
    ADCON0bits.ADON = 1;
    
    // 2 - Configure A/D interrupt (if desired)
    // * Clear ADIF bit
    // * Set ADIE bit
    // * Select interrupt priority ADIP bit
    // * Set GIE bit
    
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;
    RCONbits.IPEN = 0; // disable priority levels
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1;
    
    while(1)
    {
        // 4- Start conversion: Set GO/DONE(bar) bit
        ADCON0bits.GO = 1;
        unsigned char intPart = 0x0; //8 bits
        unsigned char tenthsPart = 0x0;

        
        unsigned char bcd; 
        
        int pot_val;
        pot_val = pot_1; //saves the last value of adc interupt to use
        
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
        
        intPart = intPart << 4; // move the integer left and mask
        intPart = intPart & 0xF0;
        tenthsPart = tenthsPart & 0x0F; //mask tenths int
        
        bcd = intPart | tenthsPart; //combine into an 8 bit
        
        PORTB = bcd; //output to port b
        
        __delay_ms(2); //delay so sseg isnt switching too fast

    }
    
    return (EXIT_SUCCESS);
}

void __interrupt() adc_sample(void) {
    // test which interrupt called this interrupt service routine
    
    // ADC Interrupt
    if(PIR1bits.ADIF && PIE1bits.ADIE)
    {    
        // 5 Wait for A/D conversion to complete by either
        // * Polling for the GO/Done bit to be cleared
        // * Waiting for the A/D interrupt
  
        // 6 - Read A/D result registers (ADRESH:ADRESL); clear bit ADIF, if required
        
        // reset the flag to avoid recursive interrupt calls
        PIR1bits.ADIF = 0;
        

        pot_1 = (ADRESH << 8) | ADRESL;
        
        
            

        
    }
}
