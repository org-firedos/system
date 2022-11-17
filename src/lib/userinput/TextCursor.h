#pragma once
#include <stdint.h>
#include "../math.h"
#include "../IO.h"

#ifndef VGA_WIDTH
#define VGA_WIDTH 80
#endif

class TextCursor
{
    private:
        uint8_t start;
        uint8_t end;
        int x;
        int y;
        bool isenabled;
        void* res0;
    public:
        void Enable();
        void Disable();
        void SetShape(uint8_t start, uint8_t end);
        void Update(int x, int y);
        Point GetPosition();
        void SetPosition(Point pos);
        void Init();
};

