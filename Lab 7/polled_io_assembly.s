config OSC = INTIO2
config BOR = OFF        ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#include <xc.inc>
	goto main	
	

	
psect code

main: 

    ; set the I/O port directions
    setf    ADCON1, a   ; AN inputs are now digital inputs
    bcf	    TRISD, 1, a 
    bsf	    TRISB, 1, a 
	
 

loop:
    btfsc   PORTB, 1, a	 
    bsf	    PORTD, 1, a	    ; 
    call    clearD	    ;
    call    delay2550us	    ; 
    bra	    loop
    
;--------------------------------------------------------------------------
    ; SUBROUTINES
clearD:
    bcf PORTD, 1, a
    return

delay2550us:			    ; 2550 us delay
	movlw	255
l1:	decf	WREG, w, a
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bnz	l1
	return 1	
end



