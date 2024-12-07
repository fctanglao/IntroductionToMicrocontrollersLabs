/* 
 * File:   lcd.c
 * Author: francis
 *
 * Created on July 23, 2024, 4:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "LiquidCrystal.h"

/*
 * Add a new function to the driver called print_int()
 * Connect the LCD data pins to PORTA
 * Connect the LCD signal pins to the LSB of PORTD
 * Connect 3 push buttons to the LSB of PORTB
 * The push buttons should increment, decrement, and reset the counter
 */

/*
 * 
 */

#define _XTAL_FREQ 1000000
#define BLUE PORTBbits.RB0
#define GREEN PORTBbits.RB1
#define RED PORTBbits.RB2

volatile long long int count;

int main() {
    // Signal pins connected to PORTD
    // RS = RD0
    // RW = RD1
    // E  = RD2
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    
    // Data pins connected to PORTA (input of LCD, but an output of PIC)
    // Remember we are programming the PIC not the LCD
    TRISA = 0;
    
    // Connect the LCD pins to the appropriate PORT pins
    pin_setup(&PORTA, &PORTD);
    
    // Initialize the LCD to be 16x2 with 5x8 dot size
    begin(16, 2, LCD_5x8DOTS);
    
    // Configure analog pins, voltage references, and digital I/O
    ADCON1 = 0x0E;
    
    // Push buttons connected to PORTB
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    
    // Select A/D conversion clock
    ADCON2bits.ADCS = 0;
    
    // Select A/D acquisition time
    ADCON2bits.ACQT = 1;
    
    // Select A/D justification
    ADCON2bits.ADFM = 1;
    
    // Select A/D input channel
    ADCON0bits.CHS = 0;
    
    // Turn on A/D module
    ADCON0bits.ADON = 1;
    
    print("Count: 0");
    
    while(1)
    {
        // Start conversion
        ADCON0bits.GO = 1;
        
        if(BLUE == 0)
        {
            home();
            displayON();
            count = count + 1;
            print("Count: ");
            print_int(count);
            print("        ");
            __delay_ms(500);
        }
        else if(GREEN == 0)
        {
            home();
            displayON();
            count = count - 1;
            print("Count: ");
            print_int(count);
            print("        ");
            __delay_ms(500);
        }
        else if(RED == 0)
        {
            home();
            displayON();
            count = 0;
            print("Count: ");
            print_int(count);
            print("        ");
            __delay_ms(500);
        }
    }
    
    return (EXIT_SUCCESS);
}



