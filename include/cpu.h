/**
 * cpu.h
 * Central processing unit
 */

#pragma once

#include "common.h"
#include "instructions.h"
#include "emu.h"

#define CPU_FLAG_Z BIT_GET(ctx->registers.f, 7)
#define CPU_FLAG_C BIT_GET(ctx->registers.f, 4)

typedef struct {
    uint8_t a;      // Accumulator
    uint8_t f;      // Flags
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;    // Stack pointer
    uint16_t pc;    // Program counter / pointer
} cpu_registers;

typedef struct {
    cpu_registers registers;

    // Current fetch
    uint16_t fetched_data;
    uint16_t mem_dest;
    bool dest_is_mem;
    uint8_t current_opcode;
    instruction *current_instruction;

    bool halted;
    bool stepping;

    bool interrupt_master_enabled;
} cpu_context;

typedef void (*IN_PROC)(cpu_context *);

void cpu_init();
bool cpu_step();

IN_PROC inst_get_processor(instruction_type type);

uint16_t cpu_read_register(register_type rt);
void cpu_set_register(register_type rt, uint16_t val);
