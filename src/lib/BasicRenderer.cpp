#include "BasicRenderer.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

BasicRenderer* GlobalRenderer;


COLOR::COLOR(uint8_t _foreground, uint8_t _background){
    this->foreground = _foreground;
    this->background = _background;
}

void BasicRenderer::PutChar(char c){
    if (c == '\n') {
        this->Next();
        return;
    }

    if (this->Col > NUM_COLS) {
        this->Next();
    }
    

    this->Buffer[this->Col + NUM_COLS * this->Row] = (CHAR){
        character: (uint8_t) c,
        color: this->Color,
    };

    this->Col++;
}

void BasicRenderer::Next(){
    this->Col = 0;

    if (this->Row < NUM_ROWS - 1) {
        this->Row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            CHAR character = this->Buffer[col + NUM_COLS * row];
            this->Buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    this->ClearRow(NUM_ROWS - 1);
}

void BasicRenderer::SetColor(COLOR _color){
    this->Color = _color.foreground + (_color.background << 4);
}

void BasicRenderer::ClearRow(size_t index){
    struct CHAR empty = (CHAR) {
        character: ' ',
        color: this->Color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        this->Buffer[col + NUM_COLS * index] = empty;
    }
}

void BasicRenderer::ClearEx(uint8_t clearColor){
    uint8_t oldColor = this->Color;
    SetColor(COLOR(clearColor, clearColor));
    
    for (size_t i = 0; i < NUM_ROWS; i++) {
        ClearRow(i);
    }

    this->Color = oldColor;
}

void BasicRenderer::Clear(){
    ClearEx(0);
}



void BasicRenderer::Print(char* str){
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        PutChar(character);
    }
}

BasicRenderer::BasicRenderer(){
            this->Buffer = (CHAR*) 0xb8000;
            this->Col = 0;
            this->Row = 0;
            this->Color = COLOR_WHITE | COLOR_BLACK << 4;
        }