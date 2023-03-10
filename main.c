#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "emul.h"
#include "manageSDL.h"

int main(int argc, char ** argv){
    struct Chip8 chip8;

    srand(time(NULL));

    if(initChip8(&chip8)== EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    if(argc<2){
        loadROM(&(chip8.cpu), "roms/BC_test.ch8");
    }
    else{
        loadROM(&(chip8.cpu), argv[1]);
    }
    emulateChip8(&chip8);

    destroyScreen(&(chip8.screen));

    return EXIT_SUCCESS;
}