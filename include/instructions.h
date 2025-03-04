/**
 * instructions.h
 * Instructions for CPU
 */

#pragma once

#include "common.h"

typedef enum {
    IT_NONE,
    IT_NOP,
    IT_LD,
    IT_INC,
    IT_DEC,
    IT_RLCA,
    IT_ADD,
    IT_RRCA,
    IT_STOP,
    IT_RLA,
    IT_JR,
    IT_RRA,
    IT_DAA,
    IT_CPL,
    IT_SCF,
    IT_CCF,
    IT_HALT,
    IT_ADC,
    IT_SUB,
    IT_SBC,
    IT_AND,
    IT_XOR,
    IT_OR,
    IT_CP,
    IT_RET,
    IT_POP,
    IT_JP,
    IT_CALL,
    IT_PUSH,
    IT_RST,
    IT_RETI,
    IT_DI,
    IT_EI,
    // CB instructions
    IT_RLC,
    IT_RRC,
    IT_RL,
    IT_RR,
    IT_SLA,
    IT_SRA,
    IT_SWAP,
    IT_SRL,
    IT_BIT,
    IT_RES,
    IT_SET,
} instruction_type;

typedef enum {
    AM_IMP,     // Implied
    AM_R_D16,   // D16 to register
    AM_R_R,     // Register to register
    AM_MR_R,    // Register to memory location of register
    AM_R,       // Single register
    AM_R_D8,    // D8 to register
    AM_R_MR,
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16,
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16,
} address_mode;

typedef enum {
    RT_NONE,
    // 8-bit registers
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    // 16-bit registers
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC,
} register_type;

typedef enum {
    CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C,
} condition_type;

typedef struct {
    instruction_type type;
    address_mode mode;
    register_type register_1;
    register_type register_2;
    condition_type condition;
    uint8_t param;
} instruction;

instruction *get_instruction_from_opcode(uint8_t opcode);
char *get_instruction_name(instruction_type t);
