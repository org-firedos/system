#pragma once
#include "math.h"

void OutByte(uint16_t port, uint8_t val);
uint8_t InByte(uint16_t port);
void IoWait();