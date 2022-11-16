#include "interrupts.h"

#pragma region PIC
    void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);

}
#pragma endregion

__attribute__((interrupt))void PageFault_Handler(struct interrupt_frame* frame)
{

    GlobalRenderer->Print("Hello World");

    while (true)
    {
        asm ("hlt");
    }
    

    PIC_EndMaster();
};

__attribute__((interrupt))void DefaultInt_Handler(struct interrupt_frame* frame)
{
    PIC_EndSlave();
};

char* InputBuffer;

__attribute__((interrupt))void KeyboardInt_Handler(struct interrupt_frame* frame)
{
    
    // Make somthing whene key is pressed!

    PIC_EndMaster();
};

