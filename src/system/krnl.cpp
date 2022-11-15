#include "../lib/BasicRenderer.h"

#pragma region MultiBoot2
    
#pragma endregion

extern "C" int kernel_main(){


    BasicRenderer __r__ = BasicRenderer();
    BasicRenderer* pRenderer = &__r__;
    
    pRenderer->Clear();
    pRenderer->Print("Hello World!");
    

    while (true)
    {
        /* code */
    }
    
}