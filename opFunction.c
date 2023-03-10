#include <stdint.h>
#include <stdlib.h>
#include "emul.h"

uint8_t random8bit(){
    double rng = rand();
    rng = rng / ((double) RAND_MAX);
    return (uint8_t) (0xFF * rng);
}

void opcode_00E0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    clearScreen(&(chip8->screen));
}

void opcode_0NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){

}

void opcode_1NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.cur = (b3 << 8) + (b2 << 4) + b1 - 2;
}

void opcode_2NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.stack[chip8->cpu.stackNb] = chip8->cpu.cur;
    if(chip8->cpu.stackNb < STACK_SIZE)
        chip8->cpu.stackNb++;
    else
        printf("Error stack overflow\n");
    chip8->cpu.cur = (b3 << 8) + (b2 << 4) + b1 - 2;
}

void opcode_00EE(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.stackNb>0){
        chip8->cpu.stackNb--;
        chip8->cpu.cur = chip8->cpu.stack[chip8->cpu.stackNb];
    }
    else{
        printf("Error trying to de-stack on empty stack\n");
    }
}

void opcode_3XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.reg[b3] == (b2<<4) + b1)
        chip8->cpu.cur += 2;
}

void opcode_4XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.reg[b3] != (b2<<4) + b1)
        chip8->cpu.cur += 2;
}

void opcode_5XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.reg[b3] == chip8->cpu.reg[b2])
        chip8->cpu.cur += 2;
}

void opcode_6XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = (b2 << 4) + b1;
}

void opcode_7XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] += (b2 << 4) + b1;
}

void opcode_8XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = chip8->cpu.reg[b2];
}

void opcode_8XY1(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = chip8->cpu.reg[b3] | chip8->cpu.reg[b2];
}

void opcode_8XY2(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = chip8->cpu.reg[b2] & chip8->cpu.reg[b3];
}

void opcode_8XY3(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = chip8->cpu.reg[b2] ^ chip8->cpu.reg[b3];
}

void opcode_8XY4(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    cpu->reg[0xF] = cpu->reg[b3] > 0xFF - cpu->reg[b2];
    cpu->reg[b3] += cpu->reg[b2];
}

void opcode_8XY5(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    cpu->reg[0xF] = (cpu->reg[b2] < cpu->reg[b3])? 1:0;
    cpu->reg[b3] = cpu->reg[b3] - cpu->reg[b2];
}

void opcode_8XY6(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[0xF] = (chip8->cpu.reg[b3] & 0x1);
    chip8->cpu.reg[b3] = chip8->cpu.reg[b3] >> 1;
}

void opcode_8XY7(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    cpu->reg[0xF] = (cpu->reg[b3] < cpu->reg[b2])? 1 : 0;
    cpu->reg[b3] = cpu->reg[b2] - cpu->reg[b3];
}

void opcode_8XYE(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[0xF] = (chip8->cpu.reg[b3] >> 7) & 0x1;
    chip8->cpu.reg[b3] = (chip8->cpu.reg[b3] << 1);
}

void opcode_9XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.reg[b3] != chip8->cpu.reg[b2])
        chip8->cpu.cur += 2;
}

void opcode_ANNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.I = (b3 << 8) + (b2 << 4) + b1;
}

void opcode_BNNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.cur = chip8->cpu.reg[0x0] + (b3 << 8) + (b2 << 4) + b1 - 2;
}

void opcode_CXNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    cpu->reg[b3] = ((b2 << 4) + b1 ) & random8bit();
}

void opcode_DXYN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    struct Screen * screen = &(chip8->screen);
    size_t x = cpu->reg[b3];
    size_t y = cpu->reg[b2];

    for(size_t j = 0; j<b1; j++){
        for(size_t i=0; i<8; i++){
            uint8_t px = (cpu->mem[cpu->I+j] & (0b10000000 >> i) );
            if(px && (x+i<PIXEL_BY_WIDTH) && (y+j<PIXEL_BY_HEIGHT)){
                if(screen->screen[x+i][y+j])
                    cpu->reg[0xF] = 1;
                screen->screen[x+i][y+j] = (screen->screen[x+i][y+j] == 1)? 0 : 1;
            }
        }
    }
}

void opcode_FX07(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.reg[b3] = chip8->cpu.sysCounter;
}

void opcode_FX15(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.sysCounter = chip8->cpu.reg[b3];
}

void opcode_FX18(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.soundCounter = chip8->cpu.reg[b3];
}

void opcode_FX1E(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    //Subjected to be an optionnal choice
    chip8->cpu.reg[0xF] = (chip8->cpu.I > 0xFFF - chip8->cpu.reg[b3])? 1:0;
    chip8->cpu.I += chip8->cpu.reg[b3];
}

void opcode_FX29(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    chip8->cpu.I = 5 * chip8->cpu.reg[b3];
}

void opcode_FX33(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    uint8_t nb = cpu->reg[b3];
    cpu->mem[cpu->I+2] = nb % 10;
    cpu->mem[cpu->I+1] = (nb/10) % 10;
    cpu->mem[cpu->I] = nb/100;
}

void opcode_FX55(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    for(size_t i = 0; i<=b3; i++){
        cpu->mem[cpu->I + i] = cpu->reg[i];
    }
    cpu->I += b3+1;
}

void opcode_FX65(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    for(size_t i = 0; i<=b3; i++){
        cpu->reg[i] = cpu->mem[cpu->I + i];
    }
    cpu->I += b3+1;
}

void opcode_EXA1(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(!(chip8->cpu.input[chip8->cpu.reg[b3]])){
        chip8->cpu.cur += 2;
    }
}

void opcode_EX9E(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    if(chip8->cpu.input[chip8->cpu.reg[b3]]){
        chip8->cpu.cur += 2;
    }
}

void opcode_FX0A(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3){
    struct cpu8 * cpu = &(chip8->cpu);
    if(cpu->waitingFX0A){
        for(int i = 0; i< INPUT_NB; i++){
            if(cpu->oldInput[i] != cpu->input[i]){
                cpu->waitingFX0A = SDL_FALSE;
                cpu->reg[cpu->vx] = i;
                return;
            }
        }
    }
    else{
        cpu->waitingFX0A = SDL_TRUE;
        printf("Entering FX0A mode\n");
        cpu->vx = b3;
        memcpy(cpu->oldInput, cpu->input, sizeof(cpu->oldInput));
    }
}
