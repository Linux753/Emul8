#include <stdio.h>
#include <stdlib.h>
#include "emul.h"
#include "manageSDL.h"
#include "opFunction.h"

void clearScreen(struct Screen * screen){
    memset(&(screen->screen), 0, sizeof(screen->screen));
}

void testScreen(struct Screen * screen){
    for(int i = 0; i<PIXEL_BY_WIDTH; i++){
        for(int j = 0; j<PIXEL_BY_HEIGHT; j++){
            screen->screen[i][j] = (uint8_t) (i*j)%2;
        }
    }
}

void initControl(struct Control * control){
    memset(control, SDL_FALSE, sizeof(*control));
}


void initMemFont(Uint8 *memory)
{
    memory[0]=0xF0;memory[1]=0x90;memory[2]=0x90;memory[3]=0x90; memory[4]=0xF0; // O
    memory[5]=0x20;memory[6]=0x60;memory[7]=0x20;memory[8]=0x20;memory[9]=0x70; // 1
    memory[10]=0xF0;memory[11]=0x10;memory[12]=0xF0;memory[13]=0x80; memory[14]=0xF0; // 2
    memory[15]=0xF0;memory[16]=0x10;memory[17]=0xF0;memory[18]=0x10;memory[19]=0xF0; // 3
    memory[20]=0x90;memory[21]=0x90;memory[22]=0xF0;memory[23]=0x10;memory[24]=0x10; // 4
    memory[25]=0xF0;memory[26]=0x80;memory[27]=0xF0;memory[28]=0x10;memory[29]=0xF0; // 5
    memory[30]=0xF0;memory[31]=0x80;memory[32]=0xF0;memory[33]=0x90;memory[34]=0xF0; // 6
    memory[35]=0xF0;memory[36]=0x10;memory[37]=0x20;memory[38]=0x40;memory[39]=0x40; // 7
    memory[40]=0xF0;memory[41]=0x90;memory[42]=0xF0;memory[43]=0x90;memory[44]=0xF0; // 8
    memory[45]=0xF0;memory[46]=0x90;memory[47]=0xF0;memory[48]=0x10;memory[49]=0xF0; // 9
    memory[50]=0xF0;memory[51]=0x90;memory[52]=0xF0;memory[53]=0x90;memory[54]=0x90; // A
    memory[55]=0xE0;memory[56]=0x90;memory[57]=0xE0;memory[58]=0x90;memory[59]=0xE0; // B
    memory[60]=0xF0;memory[61]=0x80;memory[62]=0x80;memory[63]=0x80;memory[64]=0xF0; // C
    memory[65]=0xE0;memory[66]=0x90;memory[67]=0x90;memory[68]=0x90;memory[69]=0xE0; // D
    memory[70]=0xF0;memory[71]=0x80;memory[72]=0xF0;memory[73]=0x80;memory[74]=0xF0; // E
    memory[75]=0xF0;memory[76]=0x80;memory[77]=0xF0;memory[78]=0x80;memory[79]=0x80; // F
}



void initCPU(struct cpu8 * cpu){
    memset(cpu, 0, sizeof(*cpu));
    
    cpu->cur = CURSOR0;
    cpu->nextDecrement = SDL_GetTicks() + DECREMENT;
    cpu->waitingFX0A = SDL_FALSE;

    initMemFont(cpu->mem);
}

void initJumpTable(struct SJump * jumpTable){
    jumpTable->mask[0]= 0x0000;  jumpTable->id[0]=0x0FFF;           /* 0NNN */
    jumpTable->mask[1]= 0xFFFF;  jumpTable->id[1]=0x00E0;           /* 00E0 */
    jumpTable->mask[2]= 0xFFFF;  jumpTable->id[2]=0x00EE;           /* 00EE */
    jumpTable->mask[3]= 0xF000;  jumpTable->id[3]=0x1000;           /* 1NNN */
    jumpTable->mask[4]= 0xF000;  jumpTable->id[4]=0x2000;           /* 2NNN */
    jumpTable->mask[5]= 0xF000;  jumpTable->id[5]=0x3000;           /* 3XNN */
    jumpTable->mask[6]= 0xF000;  jumpTable->id[6]=0x4000;           /* 4XNN */
    jumpTable->mask[7]= 0xF00F;  jumpTable->id[7]=0x5000;           /* 5XY0 */
    jumpTable->mask[8]= 0xF000;  jumpTable->id[8]=0x6000;           /* 6XNN */
    jumpTable->mask[9]= 0xF000;  jumpTable->id[9]=0x7000;           /* 7XNN */
    jumpTable->mask[10]= 0xF00F; jumpTable->id[10]=0x8000;          /* 8XY0 */
    jumpTable->mask[11]= 0xF00F; jumpTable->id[11]=0x8001;          /* 8XY1 */
    jumpTable->mask[12]= 0xF00F; jumpTable->id[12]=0x8002;          /* 8XY2 */
    jumpTable->mask[13]= 0xF00F; jumpTable->id[13]=0x8003;          /* 8XY3 */
    jumpTable->mask[14]= 0xF00F; jumpTable->id[14]=0x8004;          /* 8XY4 */
    jumpTable->mask[15]= 0xF00F; jumpTable->id[15]=0x8005;          /* 8XY5 */
    jumpTable->mask[16]= 0xF00F; jumpTable->id[16]=0x8006;          /* 8XY6 */
    jumpTable->mask[17]= 0xF00F; jumpTable->id[17]=0x8007;          /* 8XY7 */
    jumpTable->mask[18]= 0xF00F; jumpTable->id[18]=0x800E;          /* 8XYE */
    jumpTable->mask[19]= 0xF00F; jumpTable->id[19]=0x9000;          /* 9XY0 */
    jumpTable->mask[20]= 0xF000; jumpTable->id[20]=0xA000;          /* ANNN */
    jumpTable->mask[21]= 0xF000; jumpTable->id[21]=0xB000;          /* BNNN */
    jumpTable->mask[22]= 0xF000; jumpTable->id[22]=0xC000;          /* CXNN */
    jumpTable->mask[23]= 0xF000; jumpTable->id[23]=0xD000;          /* DXYN */
    jumpTable->mask[24]= 0xF0FF; jumpTable->id[24]=0xE09E;          /* EX9E */
    jumpTable->mask[25]= 0xF0FF; jumpTable->id[25]=0xE0A1;          /* EXA1 */
    jumpTable->mask[26]= 0xF0FF; jumpTable->id[26]=0xF007;          /* FX07 */
    jumpTable->mask[27]= 0xF0FF; jumpTable->id[27]=0xF00A;          /* FX0A */
    jumpTable->mask[28]= 0xF0FF; jumpTable->id[28]=0xF015;          /* FX15 */
    jumpTable->mask[29]= 0xF0FF; jumpTable->id[29]=0xF018;          /* FX18 */
    jumpTable->mask[30]= 0xF0FF; jumpTable->id[30]=0xF01E;          /* FX1E */
    jumpTable->mask[31]= 0xF0FF; jumpTable->id[31]=0xF029;          /* FX29 */
    jumpTable->mask[32]= 0xF0FF; jumpTable->id[32]=0xF033;          /* FX33 */
    jumpTable->mask[33]= 0xF0FF; jumpTable->id[33]=0xF055;          /* FX55 */
    jumpTable->mask[34]= 0xF0FF; jumpTable->id[34]=0xF065;          /* FX65 */
}

void initOpFunctionTable(struct Chip8 * chip8){
    chip8->opFunction[0] = opcode_0NNN;
    chip8->opFunction[1] = opcode_00E0;
    chip8->opFunction[2] = opcode_00EE;
    chip8->opFunction[3] = opcode_1NNN;
    chip8->opFunction[4] = opcode_2NNN;
    chip8->opFunction[5] = opcode_3XNN;
    chip8->opFunction[6] = opcode_4XNN;
    chip8->opFunction[7] = opcode_5XY0;
    chip8->opFunction[8] = opcode_6XNN;
    chip8->opFunction[9] = opcode_7XNN;
    chip8->opFunction[10] = opcode_8XY0;
    chip8->opFunction[11] = opcode_8XY1;
    chip8->opFunction[12] = opcode_8XY2;
    chip8->opFunction[13] = opcode_8XY3;
    chip8->opFunction[14] = opcode_8XY4;
    chip8->opFunction[15] = opcode_8XY4;
    chip8->opFunction[16] = opcode_8XY5;
    chip8->opFunction[17] = opcode_8XY7;
    chip8->opFunction[18] = opcode_8XYE;
    chip8->opFunction[19] = opcode_9XY0;
    chip8->opFunction[20] = opcode_ANNN;
    chip8->opFunction[21] = opcode_BNNN;
    chip8->opFunction[22] = opcode_CXNN;
    chip8->opFunction[23] = opcode_DXYN;
    chip8->opFunction[24] = opcode_EX9E;
    chip8->opFunction[25] = opcode_EXA1;
    chip8->opFunction[26] = opcode_FX07;
    chip8->opFunction[27] = opcode_FX0A;
    chip8->opFunction[28] = opcode_FX15;
    chip8->opFunction[29] = opcode_FX18;
    chip8->opFunction[30] = opcode_FX1E;
    chip8->opFunction[31] = opcode_FX29;
    chip8->opFunction[32] = opcode_FX33;
    chip8->opFunction[33] = opcode_FX55;
    chip8->opFunction[34] = opcode_FX65;

}

void initKeyTable(struct Chip8 * chip8){
    SDL_Scancode * table = chip8->keyTable;
    table[0] = SDL_SCANCODE_X;
    table[1] = SDL_SCANCODE_1;
    table[2] = SDL_SCANCODE_2;
    table[3] = SDL_SCANCODE_3;
    table[4] = SDL_SCANCODE_A;
    table[5] = SDL_SCANCODE_Z;
    table[6] = SDL_SCANCODE_E;
    table[7] = SDL_SCANCODE_Q;
    table[8] = SDL_SCANCODE_S;
    table[9] = SDL_SCANCODE_D;
    table[10] = SDL_SCANCODE_W;
    table[11] = SDL_SCANCODE_C;
    table[12] = SDL_SCANCODE_4;
    table[13] = SDL_SCANCODE_R;
    table[14] = SDL_SCANCODE_F;
    table[15] = SDL_SCANCODE_V;
}

int initChip8(struct Chip8 * chip8){
    if(EXIT_SUCCESS != initScreen(&(chip8->screen))){
        return EXIT_FAILURE;
    }
    initCPU(&(chip8->cpu));
    initControl(&(chip8->control));
    initJumpTable(&(chip8->jumpTable));
    initKeyTable(chip8);
    initOpFunctionTable(chip8);
    
    return EXIT_SUCCESS;
}

void decrement(struct cpu8 * cpu){
    if(SDL_TICKS_PASSED(SDL_GetTicks(), cpu->nextDecrement)){
        if(cpu->soundCounter!=0){
            cpu->soundCounter--;
        }
        if(cpu->sysCounter!=0){
            cpu->sysCounter--;
        }
        cpu->nextDecrement = SDL_GetTicks() + DECREMENT;
    }
}

int loadROM(struct cpu8 * cpu, char * path){
    int ret = EXIT_FAILURE;
    FILE * rom = fopen(path, "r");
    if(rom == NULL){
        perror("fopen");
        goto loadROMend;
    }
    for(size_t i = CURSOR0; i<MEMORY_SIZE; i++){
        if(fread(&(cpu->mem[i]), sizeof(uint8_t), 1, rom) != 1){
            fprintf(stderr, "Error reading rom, %s\n", path);
            goto loadROMend;
        }
        printf("%d\n", cpu->mem[i]);
    }
    ret = EXIT_SUCCESS;
loadROMend:
    if(rom != NULL && fclose(rom) == EOF){
        ret = EXIT_FAILURE;
    }
    return ret;
}

void resizeWindow(struct Screen * screen){
    int w, h;
    SDL_GetWindowSize(screen->window, &w, &h);
    screen->pixelWidth = w/PIXEL_BY_WIDTH;
    screen->pixelHeight = h/PIXEL_BY_HEIGHT;
    SDL_SetWindowSize(screen->window, screen->pixelWidth * PIXEL_BY_WIDTH, screen->pixelHeight * PIXEL_BY_HEIGHT);
}

void updateInput(struct Chip8 * chip8){
    for(int i = 0; i<INPUT_NB; i++){
        chip8->cpu.input[i] = chip8->control.key[chip8->keyTable[i]];
    }
}

void analyseEvent(struct Chip8 * mach){ //Analyze event relevent to the emulator itself
    if(mach->control.resizeWindow == SDL_TRUE){
        resizeWindow(&(mach->screen));
    }
    if(mach->control.key[SDL_SCANCODE_R] == SDL_TRUE){
        renderScreen(&(mach->screen));
    }
}

uint32_t getOpCode(struct cpu8 * cpu){
    return (cpu->mem[cpu->cur] << 8) + cpu->mem[cpu->cur + 1];
}

uint8_t getAction(struct SJump * table, uint16_t opCode){
    for(int i = 0; i<OPCODE_NB; i++){
        if((table->mask[i] & opCode) == table->id[i]){
            return i;
        }
    }
    printf("Unknown operation code, %d, %d\n", opCode, table->id[20]);
    return 0;
}

void interpret(struct Chip8 * chip8){
    struct cpu8 * cpu = &(chip8->cpu);

    if(!(chip8->cpu.waitingFX0A)){
        uint16_t opCode = getOpCode(cpu);

        uint8_t b1 = opCode & 0x00F;
        uint8_t b2 = (opCode & 0x0F0) >> 4;
        uint8_t b3 = (opCode & 0xF00) >> 8;
        
        uint8_t action = getAction(&(chip8->jumpTable), opCode);
        printf("%d\n", action);

        if(action < OPCODE_NB && action>0)
            chip8->opFunction[action](chip8, b1, b2, b3);  

        cpu->cur += 2;
    }
    else{
        chip8->opFunction[27](chip8, cpu->vx, 0x0, 0xA);
    }
}

void emulateChip8(struct Chip8 * chip8){
    uint32_t opCode = 0;
    while(chip8->control.quit == SDL_FALSE){
        updateEvent(&(chip8->control));
        analyseEvent(chip8);
        updateInput(chip8);

        interpret(chip8);

        SDL_Delay(FREQUENCY);
        decrement(&(chip8->cpu));

        if(SDL_TICKS_PASSED(SDL_GetTicks(), chip8->screen.nextRefresh)){
            renderScreen(&(chip8->screen));
            chip8->screen.nextRefresh = SDL_GetTicks() + FPS;
        }
    }
}

