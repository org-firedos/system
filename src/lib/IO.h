#pragma once
#include "math.h"

#define outb(p, v) OutByte(p, v)
#define inb(p) InByte(p)
#define io_wait() IoWait()

void OutByte(uint16_t port, uint8_t val);
uint8_t InByte(uint16_t port);
void IoWait();