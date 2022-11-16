#pragma once
#include <stdint.h>
#include <stddef.h>

#include "interrupts.h"

#define IDT_TA_InterruptGate    0b10001110
#define IDT_TA_CallGate         0b10001100
#define IDT_TA_TrapGate         0b10001111


struct IDTEntry{
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
};

struct IDTDescEntry {
    uint16_t offset0; 
    uint16_t selector;  
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t ignore;
    void SetOffset(uint64_t offset);
    uint64_t GetOffset();
};


typedef struct IDRT
{
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed));

void IDTSetDescriptor(uint8_t vector, void* isr, uint8_t flags);
void IDTInit(void);
