/**
 * instructions.c
 * Instructions for CPU
 */

#include "instructions.h"

static const instruction instructions[0x100] = {
    // 0x0X
    [0x00] = { IT_NOP, AM_IMP },
    [0x01] = { IT_LD, AM_R_D16, RT_BC },
    [0x02] = { IT_LD, AM_MR_R, RT_BC, RT_A },
    [0x03] = { IT_INC, AM_R, RT_BC },
    [0x04] = { IT_INC, AM_R, RT_B },
    [0x05] = { IT_DEC, AM_R, RT_B },
    [0x06] = { IT_LD, AM_R_D8, RT_B },

    [0x08] = { IT_LD, AM_A16_R, RT_NONE, RT_SP },

    [0x0a] = { IT_LD, AM_R_MR, RT_BC, RT_A },

    [0x0e] = { IT_LD, AM_R_D8, RT_C },

    // 0x1X
    [0x11] = { IT_LD, AM_R_D16, RT_DE },
    [0x12] = { IT_LD, AM_MR_R, RT_DE, RT_A },
    [0x15] = { IT_DEC, AM_R, RT_D },
    [0x16] = { IT_LD, AM_R_D8, RT_D },
    [0x1a] = { IT_LD, AM_R_MR, RT_A, RT_DE },
    [0x1e] = { IT_LD, AM_R_D8, RT_E },

    // 0x2X
    [0x21] = { IT_LD, AM_R_D16, RT_HL },
    [0x22] = { IT_LD, AM_HLI_R, RT_HL, RT_A },
    [0x25] = { IT_DEC, AM_R, RT_H },
    [0x26] = { IT_LD, AM_R_D8, RT_H },
    [0x2a] = { IT_LD, AM_R_HLI, RT_A, RT_HL },
    [0x2e] = { IT_LD, AM_R_D8, RT_L },

    // 0x3X
    [0x31] = { IT_LD, AM_R_D16, RT_SP },
    [0x32] = { IT_LD, AM_HLD_R, RT_HL, RT_A },
    [0x35] = { IT_DEC, AM_R, RT_HL },
    [0x36] = { IT_LD, AM_MR_D8, RT_HL },
    [0x3a] = { IT_LD, AM_R_HLD, RT_A, RT_HL },
    [0x3e] = { IT_LD, AM_R_D8, RT_A },

    // 0x4X
    [0x40] = { IT_LD, AM_R_R, RT_B, RT_B },
    [0x41] = { IT_LD, AM_R_R, RT_B, RT_C },
    [0x42] = { IT_LD, AM_R_R, RT_B, RT_D },
    [0x43] = { IT_LD, AM_R_R, RT_B, RT_E },
    [0x44] = { IT_LD, AM_R_R, RT_B, RT_H },
    [0x45] = { IT_LD, AM_R_R, RT_B, RT_L },
    [0x46] = { IT_LD, AM_R_MR, RT_B, RT_HL },
    [0x47] = { IT_LD, AM_R_R, RT_B, RT_A },
    [0x48] = { IT_LD, AM_R_R, RT_C, RT_B },
    [0x49] = { IT_LD, AM_R_R, RT_C, RT_C },
    [0x4a] = { IT_LD, AM_R_R, RT_C, RT_D },
    [0x4b] = { IT_LD, AM_R_R, RT_C, RT_E },
    [0x4c] = { IT_LD, AM_R_R, RT_C, RT_H },
    [0x4d] = { IT_LD, AM_R_R, RT_C, RT_L },
    [0x4e] = { IT_LD, AM_R_MR, RT_C, RT_HL },
    [0x4f] = { IT_LD, AM_R_R, RT_C, RT_A },

    // 0x5X
    [0x50] = { IT_LD, AM_R_R,  RT_D, RT_B },
    [0x51] = { IT_LD, AM_R_R,  RT_D, RT_C },
    [0x52] = { IT_LD, AM_R_R,  RT_D, RT_D },
    [0x53] = { IT_LD, AM_R_R,  RT_D, RT_E },
    [0x54] = { IT_LD, AM_R_R,  RT_D, RT_H },
    [0x55] = { IT_LD, AM_R_R,  RT_D, RT_L },
    [0x56] = { IT_LD, AM_R_MR, RT_D, RT_H },
    [0x57] = { IT_LD, AM_R_R,  RT_D, RT_A },
    [0x58] = { IT_LD, AM_R_R,  RT_E, RT_B },
    [0x59] = { IT_LD, AM_R_R,  RT_E, RT_C },
    [0x5a] = { IT_LD, AM_R_R,  RT_E, RT_D },
    [0x5b] = { IT_LD, AM_R_R,  RT_E, RT_E },
    [0x5c] = { IT_LD, AM_R_R,  RT_E, RT_H },
    [0x5d] = { IT_LD, AM_R_R,  RT_E, RT_L },
    [0x5e] = { IT_LD, AM_R_MR, RT_E, RT_HL },
    [0x5f] = { IT_LD, AM_R_R,  RT_E, RT_A },

    // 0x6X
    [0x60] = { IT_LD, AM_R_R,  RT_H, RT_B },
    [0x61] = { IT_LD, AM_R_R,  RT_H, RT_C },
    [0x62] = { IT_LD, AM_R_R,  RT_H, RT_D },
    [0x63] = { IT_LD, AM_R_R,  RT_H, RT_E },
    [0x64] = { IT_LD, AM_R_R,  RT_H, RT_H },
    [0x65] = { IT_LD, AM_R_R,  RT_H, RT_L },
    [0x66] = { IT_LD, AM_R_MR, RT_H, RT_HL },
    [0x67] = { IT_LD, AM_R_R,  RT_H, RT_A },
    [0x68] = { IT_LD, AM_R_R,  RT_L, RT_B },
    [0x69] = { IT_LD, AM_R_R,  RT_L, RT_C },
    [0x6a] = { IT_LD, AM_R_R,  RT_L, RT_D },
    [0x6b] = { IT_LD, AM_R_R,  RT_L, RT_E },
    [0x6c] = { IT_LD, AM_R_R,  RT_L, RT_H },
    [0x6d] = { IT_LD, AM_R_R,  RT_L, RT_L },
    [0x6e] = { IT_LD, AM_R_MR, RT_L, RT_HL },
    [0x6f] = { IT_LD, AM_R_R,  RT_L, RT_A },

    // 0x7X
    [0x70] = { IT_LD, AM_MR_R,  RT_HL, RT_B },
    [0x71] = { IT_LD, AM_MR_R,  RT_HL, RT_C },
    [0x72] = { IT_LD, AM_MR_R,  RT_HL, RT_D },
    [0x73] = { IT_LD, AM_MR_R,  RT_HL, RT_E },
    [0x74] = { IT_LD, AM_MR_R,  RT_HL, RT_H },
    [0x75] = { IT_LD, AM_MR_R,  RT_HL, RT_L },
    [0x76] = { IT_HALT },
    [0x77] = { IT_LD, AM_MR_R,  RT_HL, RT_A },
    [0x78] = { IT_LD, AM_R_R,  RT_A, RT_B },
    [0x79] = { IT_LD, AM_R_R,  RT_A, RT_C },
    [0x7a] = { IT_LD, AM_R_R,  RT_A, RT_D },
    [0x7b] = { IT_LD, AM_R_R,  RT_A, RT_E },
    [0x7c] = { IT_LD, AM_R_R,  RT_A, RT_H },
    [0x7d] = { IT_LD, AM_R_R,  RT_A, RT_L },
    [0x7e] = { IT_LD, AM_R_MR, RT_A, RT_HL },
    [0x7f] = { IT_LD, AM_R_R,  RT_A, RT_A },

    [0xaf] = { IT_XOR, AM_R, RT_A },

    [0xc3] = { IT_JP, AM_D16 },

    // 0xeX
    [0xe2] = { IT_LD, AM_MR_R, RT_C, RT_A },
    [0xea] = { IT_LD, AM_A16_R, RT_NONE, RT_A },


    // 0xfX
    [0xf2] = { IT_LD, AM_R_MR, RT_A, RT_C },
    [0xf3] = { IT_DI},
    [0xfa] = { IT_LD, AM_R_A16, RT_A },
};

instruction *get_instruction_from_opcode(uint8_t opcode) {
    return &instructions[opcode];
}

char *instruction_lookup[] = {
    "<NONE>",
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "RET",
    "POP",
    "JP",
    "CB",
    "CALL",
    "PUSH",
    "RST",
    "RETI",
    "DI",
    "EI",
    "LDH",
    "JPHL",
    "ERR",
    // CB instructions
    "RLC",
    "RRC",
    "RL",
    "RR",
    "SLA",
    "SRA",
    "SWAP",
    "SRL",
    "BIT",
    "RES",
    "SET",
};

char *get_instruction_name(instruction_type t) {
    return instruction_lookup[t];
}
