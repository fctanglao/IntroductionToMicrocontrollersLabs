#include <xc.inc>
    ;psect code
    ;C = A + B, A and B are 24-bit numbers
    
    ;T is top and B is bottom
    num_TL equ 0x20
    num_BL equ 0x50
    num_TM equ 0x21
    num_BM equ 0x51
    num_TR equ 0x22
    num_BR equ 0x52
    num_S1 equ 0x50
    num_S2 equ 0x51
    num_S3 equ 0x52
 
    ;A = F1 91 B5
    movlw 0xF1
    movwf num_TL, f, a
    movlw 0x91
    movwf num_TM, f, a
    movlw 0xB5
    movwf num_TR, f, a
    
    ;B = 07 A2 04
    movlw 0x07
    movwf num_BL, f, a
    movlw 0xA2
    movwf num_BM, f, a
    movlw 0x04
    movwf num_BR, f, a
    
    clrf WREG
    
    ; sum R (LSB)
    movwf num_TR, w, a
    addwfc num_BR, w, a
    
    movwf num_S3, f, a
    
    ; sum M (middle)
    movwf num_TM, w, a
    addwfc num_BM, w, a
    
    movwf num_S2, f, a
    
    ; sum L (MSB)
    movwf num_TL, w, a
    addwfc num_BL, w, a
    
    movwf num_S1, f, a
    
end

