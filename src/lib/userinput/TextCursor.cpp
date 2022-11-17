#include "TextCursor.h"


void TextCursor::Enable(){
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | this->start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | this->end);
}

void TextCursor::Disable(){
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void TextCursor::SetShape(uint8_t _start, uint8_t _end){
    this->start = _start;
    this->end = _end;
}

void TextCursor::Update(int x, int y){
    uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void TextCursor::SetPosition(Point pos){
    this->Update((int)pos.x, (int)pos.y);
}

Point TextCursor::GetPosition()
{
    Point ret;

    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    ret.x = pos % VGA_WIDTH;
    ret.y = pos % VGA_WIDTH;

    return ret;
}

void TextCursor::Init(){
    SetShape(0,15);
    Enable();
    Update(0,0);
}