#ifndef OP_FUNCTION_H
#define OP_FUNCTION_H

#include <stdint.h>
#include "emul.h"

void opcode_0NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_00E0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_00EE(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_1NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_2NNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_3XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_4XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_5XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_6XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_7XNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY1(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY2(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY3(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY4(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY5(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY6(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XY7(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_8XYE(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_9XY0(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_ANNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_BNNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_CXNN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_DXYN(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX07(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX15(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX18(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX1E(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX29(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX33(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX55(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX65(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_EXA1(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_EX9E(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);
void opcode_FX0A(struct Chip8 * chip8, uint8_t b1, uint8_t b2, uint8_t b3);


#endif