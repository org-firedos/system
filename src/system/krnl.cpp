#include "lib.h"

#include "../lib/BasicRenderer.h"

#pragma region MultiBoot2
    
#pragma endregion

extern "C" int kernel_main(){


    BasicRenderer __r__ = BasicRenderer();
    BasicRenderer* pRenderer = &__r__;

    pRenderer->Clear();
    pRenderer->Print("Hello World!\n");

    pRenderer->SetColor(COLOR(COLOR_BLUE, COLOR_DARK_GRAY));
    pRenderer->ClearEx(COLOR_DARK_GRAY);

    pRenderer->Next();


    pRenderer->Print("Welcome to FIREDOS x64!\n");
    

    while (true)
    {
        /* code */
    }
    
}