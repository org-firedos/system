#include "IO.h"

void OutByte(uint16_t port, uint8_t val){
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t InByte(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

void IoWait(){
    OutByte(0x80, 0);
}