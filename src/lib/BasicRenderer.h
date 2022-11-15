#pragma once
#include <stdint.h>
#include <stddef.h>

struct COLOR
{
    uint8_t foreground;
    uint8_t background;

    COLOR(uint8_t _foreground, uint8_t _background);
};

struct CHAR {
    uint8_t character;
    uint8_t color;
};

enum {
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_BLUE = 1,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
    COLOR_BLACK = 0,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARK_GRAY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_PINK = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15,
};

class BasicRenderer
{
    public:

        CHAR* Buffer;
        size_t Row;
        size_t Col;
        uint8_t Color;

        void Print(char* str);
        void PutChar(char c);
        void SetColor(COLOR _color);
        void Clear();
        void ClearEx(uint8_t clearColor);
        void Next();
        void ClearRow(size_t index);

        BasicRenderer();
        /*BasicRenderer(COLOR color){
            this->Buffer = (CHAR*) 0xb8000;
            this->Col = 0;
            this->Row = 0;
            this->Color = color.foreground | color.background << 4;
        }*/
        //void PrintEx(const char* str, int xpos, int ypos);
};