config OSC = INTIO2	; Oscillator (Internal oscillator block, port function on RA6 and RA7)
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>	
	goto start	
	
	; Take a BCD number using 4 switches connected to bits 0 to 3 of PORTB
	; Output the BCD number in hex to a sseg display connected to bits 0 to 6 of PORTA
	; Store in address 0x70 by storing sseg codes in data memory starting at address 0x100
	psect data

lookup:	DB  0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84, 0x88, 0xE0, 0xB1, 0xC2, 0xB0, 0xB8	
	
	psect code
SSEG	EQU 0x41
I	EQU 0x70
	
start:	
	movlw	low lookup
	movwf	TBLPTRL, a
	movlw	high lookup
	movwf	TBLPTRH, a
	movlw	low highword lookup
	movwf	TBLPTRU, a
	
	lfsr	0, SSEG
	movlw	16
	movwf	I, a
	
loop:	
	TBLRD*+
	movff	TABLAT, POSTINC0
	decf	I, f, a
	bnz	loop
	
	setf	ADCON1, a
	clrf	TRISA, a
	setf	TRISB, a
	
infiniteloop:
	movf	PORTB, w, a
	andlw	0x0f
	call	bcd2sseg, 0
	movwf	PORTA, a
	bra	infiniteloop
    
bcd2sseg:
	lfsr	0, SSEG
	movf	PLUSW0, w, a
	return	0
	
end


