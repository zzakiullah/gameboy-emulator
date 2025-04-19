/**
 * cpu_fetch.c
 * Fetch CPU instructions
 */

#include "cpu.h"
#include "bus.h"
#include "emu.h"

extern cpu_context ctx;

void fetch_data() {
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    switch (ctx.current_instruction->mode) {
        // Addressing mode implied, nothing needs to be read
        case AM_IMP:
            return;
        case AM_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_1);
            return;
        case AM_R_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_2);
            return;
        case AM_R_D8:
            ctx.fetched_data = bus_read(ctx.registers.pc);
            emu_cycles(1);
            ctx.registers.pc++;
            return;
        case AM_R_D16:
        case AM_D16:
            uint16_t low = bus_read(ctx.registers.pc);
            emu_cycles(1);

            uint16_t high = bus_read(ctx.registers.pc + 1);
            emu_cycles(1);

            ctx.fetched_data = low | (high << 8);
            ctx.registers.pc += 2;
            return;
        case AM_MR_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_2);
            ctx.mem_dest = cpu_read_register(ctx.current_instruction->register_1);
            ctx.dest_is_mem = true;
            if (ctx.current_instruction->register_1 == RT_C) {
                ctx.mem_dest |= 0xff00;
            }
            return;
        case AM_R_MR:
            uint16_t address = cpu_read_register(ctx.current_instruction->register_2);
            if (ctx.current_instruction->register_2 == RT_C) {
                address |= 0xff00;
            }
            ctx.fetched_data = bus_read(address);
            emu_cycles(1);
            return;
        case AM_R_HLI:
            ctx.fetched_data = bus_read(cpu_read_register(ctx.current_instruction->register_2));
            emu_cycles(1);
            cpu_set_register(RT_HL, cpu_read_register(RT_HL) + 1);
            return;
        case AM_R_HLD:
            ctx.fetched_data = bus_read(cpu_read_register(ctx.current_instruction->register_2));
            emu_cycles(1);
            cpu_set_register(RT_HL, cpu_read_register(RT_HL) - 1);
            return;
        case AM_HLI_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_2);
            ctx.mem_dest = cpu_read_register(ctx.current_instruction->register_1);
            ctx.dest_is_mem = true;
            cpu_set_register(RT_HL, cpu_read_register(RT_HL) + 1);
            return;
        case AM_HLD_R:
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_2);
            ctx.mem_dest = cpu_read_register(ctx.current_instruction->register_1);
            ctx.dest_is_mem = true;
            cpu_set_register(RT_HL, cpu_read_register(RT_HL) - 1);
            return;
        case AM_R_A8:
            ctx.fetched_data = bus_read(ctx.registers.pc);
            emu_cycles(1);
            ctx.registers.pc++;
            return;
        case AM_A8_R:
            ctx.mem_dest = bus_read(ctx.registers.pc) | 0xff00;
            ctx.dest_is_mem = true;
            emu_cycles(1);
            ctx.registers.pc++;
            return;
        case AM_HL_SPR:
        case AM_D8:
            ctx.fetched_data = bus_read(ctx.registers.pc);
            emu_cycles(1);
            ctx.registers.pc++;
            return;
        case AM_A16_R:
        case AM_D16_R:
            uint16_t low = bus_read(ctx.registers.pc);
            emu_cycles(1);

            uint16_t high = bus_read(ctx.registers.pc + 1);
            emu_cycles(1);

            ctx.mem_dest = low | (high << 8);
            ctx.dest_is_mem = true;

            ctx.registers.pc += 2;
            ctx.fetched_data = cpu_read_register(ctx.current_instruction->register_2);
            return;
        case AM_MR_D8:
            ctx.fetched_data = bus_read(ctx.registers.pc);
            emu_cycles(1);
            ctx.registers.pc++;
            ctx.mem_dest = cpu_read_register(ctx.current_instruction->register_1);
            ctx.dest_is_mem = true;
            return;
        case AM_MR:
            ctx.mem_dest = cpu_read_register(ctx.current_instruction->register_1);
            ctx.dest_is_mem = true;
            ctx.fetched_data = bus_read(cpu_read_register(ctx.current_instruction->register_1));
            emu_cycles(1);
            return;
        case AM_R_A16:
            uint16_t low = bus_read(ctx.registers.pc);
            emu_cycles(1);

            uint16_t high = bus_read(ctx.registers.pc + 1);
            emu_cycles(1);

            uint16_t address = low | (high << 8);

            ctx.registers.pc += 2;
            ctx.fetched_data = bus_read(address);
            emu_cycles(1);
            return;
        default:
            printf("Unknown Addressing Mode! %d (%02X)\n", ctx.current_instruction->mode, ctx.current_opcode);
            exit(-7);
            return;
    }
}
