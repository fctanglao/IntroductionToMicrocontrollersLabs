config OSC = INTIO2	; Oscillator (Internal oscillator block, port function on RA6 and RA7)
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>	
	goto start	
	
	; Take 2 3-bit BCD numbers using 6 switches connected to bits 0 to 2 and 3 to 5 of PORTD
	; Add them and output the sum in hex to a sseg display connected to bits 0 to 6 of PORTA

lookup:	DB  0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84, 0x88, 0xE0, 0xB1, 0xC2, 0xB0, 0xB8	
	
	psect code
SSEG	EQU 0x41
I	EQU 0x70
num2    EQU 0x71

	
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
	setf	TRISD, a
	
infiniteloop:
	bcf	STATUS, 0 ;clear carry
	movf	PORTD, w, a ;get right 3 bits
	andlw	0x38
	movwf	num2, a
	rrncf	num2, f, a
	rrncf	num2, f, a
	rrncf	num2, f, a
	
	movf	PORTD, w, a ;get left 3 bits
	andlw	0x07
	addwfc	num2, w, a ;add working reg with num2

	call	bcd2sseg, 0 ;get hex sseg value
	movwf	PORTA, a ; send to port a
	bra	infiniteloop
    
bcd2sseg:
	lfsr	0, SSEG
	movf	PLUSW0, w, a
	return	0
	
end
