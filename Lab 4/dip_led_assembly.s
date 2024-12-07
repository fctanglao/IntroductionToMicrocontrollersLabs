config OSC = INTIO2	; Oscillator (Internal oscillator block, port function on RA6 and RA7)
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)    
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))    
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)    
#include <xc.inc>
	goto start
	
	; If RC1 is high and RD1 is low, turn on RD0
	; If RC1 is low and RD1 is high, turn on RC0
	; If both RC1 and RD1 are high, no LEDs turn on
	; If both RC1 and RD1 are low, both LEDs turn on
	psect code

start:
	setf ADCON1, a ; turn off ADC
	movlw 00000010B
	movwf TRISC, a
	movwf TRISD, a

infloop: 
	movf PORTC, w, a
	andlw 00000010B
	bz c_off
	bcf PORTC, 0, a ; turn on c_0
	movf PORTD, w, a
	andlw 00000010B
	bz d_off
	bcf PORTD, 0, a ; turn on d_0
	bra infloop

c_off:
	bsf PORTC, 0, a ; turn off c_0
	movf PORTD, w, a
	andlw 00000010B
	bz d_off
	bcf PORTD, 0, a ; turn on d_0
	bra infloop

d_off:
	bsf PORTD, 0, a ; turn off d_0
	bra infloop
	
end
