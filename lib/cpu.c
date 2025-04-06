/**
 * cpu.c
 * Central processing unit
 */

#include "cpu.h"
#include "bus.h"

cpu_context ctx = {0};

void cpu_init() {
    // Entry point of CPU
    ctx.registers.pc = 0x100;
    ctx.registers.a = 0x01;
}

static void fetch_instruction() {
    // Read bus from program counter
    ctx.current_opcode = bus_read(ctx.registers.pc++);
    ctx.current_instruction = get_instruction_from_opcode(ctx.current_opcode);

    if (ctx.current_instruction == NULL) {
        printf("Unknown instruction: %02x (%02X)\n", ctx.current_instruction->mode, ctx.current_opcode);
        exit(-7);
    }
}

static void fetch_data() {
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    switch (ctx.current_instruction->mode) {
        // Addressing mode implied, nothing needs to be read
        case AM_IMP:
            return;
        case AM_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_1);
            return;
        case AM_R_D8:
            ctx.fetched_data = bus_read(ctx.registers.pc);
            emu_cycles(1);
            ctx.registers.pc++;
            return;
        case AM_D16:
            uint16_t low = bus_read(ctx.registers.pc);
            emu_cycles(1);

            uint16_t high = bus_read(ctx.registers.pc + 1);
            emu_cycles(1);

            ctx.fetched_data = low | (high << 8);
            ctx.registers.pc += 2;
            return;
        default:
            printf("Unknown addressing mode: %d\n", ctx.current_instruction->mode);
            exit(-7);
            return;
    }
}

static void execute() {
    printf("Executing instruction: %02x    PC: %04x\n", ctx.current_opcode, ctx.registers.pc);
    IN_PROC proc = inst_get_processor(ctx.current_instruction->type);

    if (!proc) {
        NO_IMPL;
    }

    proc(&ctx);
}

bool cpu_step() {
    if (!ctx.halted) {
        uint16_t pc = ctx.registers.pc;

        fetch_instruction();
        fetch_data();

        printf("%04X: %-7s (%02X %02X %02X) A: %02X B: %02X C: %02X\n", 
            pc, inst_name(ctx.current_instruction->type), ctx.current_opcode,
            bus_read(pc + 1), bus_read(pc + 2), ctx.registers.a, ctx.registers.b, ctx.registers.c);

        execute();
    }

    return true;
}
