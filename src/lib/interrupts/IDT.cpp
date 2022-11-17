#include "IDT.h"

static IDRT idtr;
__attribute__((aligned(0x10)))
static IDTEntry idt[256]; // Create an array of IDT entries; aligned for performance
static bool vectors[256];

void IDTSetDescriptor(uint8_t vector, void* isr, uint8_t flags){
    IDTEntry* descriptor = &idt[vector];
 
    descriptor->isr_low       = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved        = 0;
}

void IDTInit(){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(IDTEntry) * 256 - 1;
 
    /*for (uint8_t vector = 0; vector < 32; vector++) {
        IDTSetDescriptor(vector, (void*)DefaultInt_Handler , 0x8E);
        vectors[vector] = true;
    }*/
 
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT

    RemapPIC();

    outb(PIC1_DATA, 0b11111101);
    outb(PIC2_DATA, 0b11111111);

    __asm__ volatile ("sti"); // set the interrupt flag
}