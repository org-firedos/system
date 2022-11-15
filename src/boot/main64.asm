global long_mode_start
extern kernel_main

; ???

section .text
bits 64

long_mode_start:
    ; load null into all data segment registers
    mov ax, 0 ; TIME TO SEE
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    

	;   ------ KernelMode(asm) ------
    ;     
    ;     -Init something in asm
    ;
    ;     -Load the 'C++' System (system/krnl.cpp)
    ;

    ; Now we call teh C entry point


    call kernel_main

    hlt ; Halts the cpu !