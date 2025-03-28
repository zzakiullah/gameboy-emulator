/**
 * instructions.c
 * Instructions for CPU
 */

#include "instructions.h"

static const instruction instructions[0x100] = {
    [0x00] = { IT_NOP, AM_IMP },
    [0x01] = { IT_LD, AM_R_D16, RT_BC },
    [0x02] = { IT_LD, AM_MR_R, RT_BC, RT_A },
    [0x03] = { IT_INC, AM_R, RT_BC },
    [0x04] = { IT_INC, AM_R, RT_B },
    [0x05] = { IT_DEC, AM_R, RT_B },
    [0x0e] = { IT_LD, AM_R_D8, RT_C },
    [0xaf] = { IT_XOR, AM_R, RT_A },
    [0xc3] = { IT_JP, AM_D16 },
    [0xf3] = { IT_DI },
};

instruction *get_instruction_from_opcode(uint8_t opcode) {
    if (instructions[opcode].type == IT_NONE) {
        return NULL;
    }
    return &instructions[opcode];
}

char *get_instruction_name(instruction_type t) {
    
}
