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

extern "C" int kernel_main(){
    IDTInit();

    IDTSetDescriptor(0xE, (void*)&PageFault_Handler, IDT_TA_InterruptGate);
    
    IDTSetDescriptor(0x21, (void*)&KeyboardInt_Handler, IDT_TA_InterruptGate);

    BasicRenderer __r__ = BasicRenderer();
    BasicRenderer* pRenderer = &__r__;

    

    //pRenderer->Clear();
    pRenderer->Print("Hello World!\n");

    pRenderer->SetColor(COLOR(COLOR_BLUE, COLOR_DARK_GRAY));
    pRenderer->ClearEx(COLOR_DARK_GRAY);

    pRenderer->Next();


    pRenderer->Print("Welcome to FIREDOS x64!\n");
    
    //if(are_interrupts_enabled())pRenderer->Print("\nInterupts!\n");



    while (true)
    {
        /* code */
    }
    
}

