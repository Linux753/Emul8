#ifndef EMUL_H
#define EMUL_H

#define MEMORY_SIZE 4096
#define CURSOR0 0x200
#define OPCODE_NB 35
#define STACK_SIZE 16

#define PIXEL_DIM 8
#define PIXEL_BY_WIDTH 64
#define PIXEL_BY_HEIGHT 32
#define SCREEN_WIDTH PIXEL_BY_WIDTH*PIXEL_DIM
#define SCREEN_HEIGHT PIXEL_BY_HEIGHT*PIXEL_DIM
#define FPS 16 //Nb of millisecond by
#define DECREMENT 16
#define FREQUENCY 4
#define INPUT_NB 16

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

struct SJump{
    uint16_t mask[OPCODE_NB];
    uint16_t id[OPCODE_NB];
};

struct cpu8{
    uint8_t mem[MEMORY_SIZE];
    uint16_t cur;
    uint8_t reg[16];
    uint16_t I;
    
    uint16_t stack[STACK_SIZE];
    uint8_t stackNb;
    
    uint8_t sysCounter;
    uint8_t soundCounter;
    uint32_t nextDecrement;

    SDL_bool input[INPUT_NB];
    
    //FX0A special variable
    SDL_bool oldInput[INPUT_NB];
    SDL_bool waitingFX0A;
    uint8_t vx;

};

struct Screen{
    SDL_Window * window;
    SDL_Renderer * renderer;
    uint8_t screen[PIXEL_BY_WIDTH][PIXEL_BY_HEIGHT];
    uint32_t pixelHeight;
    uint32_t pixelWidth;
    uint32_t nextRefresh;
};

struct Control{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    SDL_bool resizeWindow;
};

struct Chip8{
    struct cpu8 cpu;
    struct Screen screen;
    struct Control control;
    SDL_Scancode keyTable[INPUT_NB];
    void (* opFunction[OPCODE_NB]) (struct Chip8 *, uint8_t, uint8_t, uint8_t);
    struct SJump jumpTable;
};



void testScreen(struct Screen * screen);
int initChip8(struct Chip8 * chip8);
void analyseEvent(struct Chip8 * mach);
void emulateChip8(struct Chip8 * chip8);
void clearScreen(struct Screen * screen);
int loadROM(struct cpu8 * cpu, char * path);


#endif

