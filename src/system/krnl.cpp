#include "../lib/BasicRenderer.h"
#include "../lib/interrupts/IDT.h"
#include "../lib/interrupts/interrupts.h"

static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) ); 
    return flags & (1 << 9);
} // Is only for testing :) 

BasicRenderer  r = BasicRenderer();

extern "C" int kernel_main(){
    IDTInit();

    r = BasicRenderer();
    GlobalRenderer = &r;

    IDTSetDescriptor(0xE, (void*)&PageFault_Handler, IDT_TA_InterruptGate);
    
    IDTSetDescriptor(0x21, (void*)&KeyboardInt_Handler, IDT_TA_InterruptGate);

    

    

    //pRenderer->Clear();
    GlobalRenderer->Print("Hello World!");

    GlobalRenderer->SetColor(COLOR(COLOR_BLUE, COLOR_DARK_GRAY));
    GlobalRenderer->ClearEx(COLOR_DARK_GRAY);

    //GlobalRenderer->Next();


    GlobalRenderer->Print("Welcome to FIREDOS x64!");
    
    //if(are_interrupts_enabled())pRenderer->Print("\nInterupts!\n");



    while (true)
    {
        /* code */
    }
    
}

