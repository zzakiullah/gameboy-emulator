/**
 * cpu_proc.c
 * Process CPU instructions
 */

#include "cpu.h"
#include "emu.h"

static bool check_cond(cpu_context *ctx) {
    bool z = CPU_FLAG_Z;
    bool c = CPU_FLAG_C;

    switch (ctx->current_instruction->condition) {
        case CT_NONE:   return true;
        case CT_C:      return c;
        case CT_NC:     return !c;
        case CT_Z:      return z;
        case CT_NZ:     return !z;
        // Should not reach here
        default:        return false;
    }
}

void cpu_set_flags(cpu_context *ctx, char z, char n, char h, char c) {
    if (z != -1) {
        BIT_SET(ctx->registers.f, 7, z);
    }
    if (n != -1) {
        BIT_SET(ctx->registers.f, 6, n);
    }
    if (h != -1) {
        BIT_SET(ctx->registers.f, 5, h);
    }
    if (c != -1) {
        BIT_SET(ctx->registers.f, 4, c);
    }
}

static void proc_none(cpu_context *ctx) {
    printf("Invalid instruction!\n");
    exit(-7);
}

static void proc_nop(cpu_context *ctx) {}

static void proc_ld(cpu_context *ctx) {
    if (ctx->dest_is_mem) {
        // If 16-bit register
        if (ctx->current_instruction->register_2 >= RT_AF) {
            emu_cycles(1);
            bus_write16(ctx->mem_dest, ctx->fetched_data);
        }
        else {
            bus_write(ctx->mem_dest, ctx->fetched_data);
        }
    }
    else if (ctx->current_instruction->mode == AM_HL_SPR) {
        uint8_t hflag = (cpu_read_reg(ctx->current_instruction->register_2) & 0xf) + 
            (ctx->fetched_data & 0xf) >= 0x10;

        // Carry flag
        uint8_t cflag = (cpu_read_reg(ctx->current_instruction->register_2) & 0xff) + 
            (ctx->fetched_data & 0xff) >= 0x100;

        cpu_set_flags(ctx, 0, 0, hflag, cflag);
        cpu_set_reg(ctx->current_instruction->register_1, 
            cpu_read_reg(ctx->current_instruction->register_2) + (char)ctx->fetched_data);
    }
    else {
        cpu_set_register(ctx->current_instruction->register_1, ctx->fetched_data);
    }
}

static void proc_inc(cpu_context *ctx) {

}

static void proc_dec(cpu_context *ctx) {

}

static void proc_rlca(cpu_context *ctx) {

}

static void proc_add(cpu_context *ctx) {

}

static void proc_rrca(cpu_context *ctx) {

}

static void proc_stop(cpu_context *ctx) {

}

static void proc_rla(cpu_context *ctx) {

}

static void proc_jr(cpu_context *ctx) {

}

static void proc_rra(cpu_context *ctx) {

}

static void proc_daa(cpu_context *ctx) {

}

static void proc_cpl(cpu_context *ctx) {

}

static void proc_scf(cpu_context *ctx) {

}

static void proc_ccf(cpu_context *ctx) {

}

static void proc_halt(cpu_context *ctx) {

}

static void proc_adc(cpu_context *ctx) {

}

static void proc_sub(cpu_context *ctx) {

}

static void proc_sbc(cpu_context *ctx) {

}

static void proc_and(cpu_context *ctx) {

}

static void proc_xor(cpu_context *ctx) {
    ctx->registers.a ^= ctx->fetched_data & 0xff;
    cpu_set_flags(ctx, ctx->registers.a == 0, 0, 0, 0);
}

static void proc_or(cpu_context *ctx) {

}

static void proc_cp(cpu_context *ctx) {

}

static void proc_ret(cpu_context *ctx) {

}

static void proc_pop(cpu_context *ctx) {

}

static void proc_jp(cpu_context *ctx) {
    if (check_cond(ctx)) {
        ctx->registers.pc = ctx->fetched_data;
        emu_cycles(1);
    }
}

static void proc_cb(cpu_context *ctx) {

}

static void proc_call(cpu_context *ctx) {

}

static void proc_push(cpu_context *ctx) {

}

static void proc_rst(cpu_context *ctx) {

}

static void proc_reti(cpu_context *ctx) {

}

static void proc_di(cpu_context *ctx) {
    ctx->interrupt_master_enabled = false;
}

static void proc_ei(cpu_context *ctx) {

}

static void proc_rlc(cpu_context *ctx) {

}

static void proc_rrc(cpu_context *ctx) {

}

static void proc_rl(cpu_context *ctx) {

}

static void proc_rr(cpu_context *ctx) {

}

static void proc_sla(cpu_context *ctx) {

}

static void proc_sra(cpu_context *ctx) {

}

static void proc_swap(cpu_context *ctx) {

}

static void proc_srl(cpu_context *ctx) {

}

static void proc_bit(cpu_context *ctx) {

}

static void proc_res(cpu_context *ctx) {

}

static void proc_set(cpu_context *ctx) {

}

static void proc_ldh(cpu_context *ctx) {

}

static void proc_jphl(cpu_context *ctx) {

}

static void proc_err(cpu_context *ctx) {

}

static IN_PROC processors[] = {
    [IT_NONE]   = proc_none,
    [IT_NOP]    = proc_nop,
    [IT_LD]     = proc_ld,
    [IT_INC]    = proc_inc,
    [IT_DEC]    = proc_dec,
    [IT_RLCA]   = proc_rlca,
    [IT_ADD]    = proc_add,
    [IT_RRCA]   = proc_rrca,
    [IT_STOP]   = proc_stop,
    [IT_RLA]    = proc_rla,
    [IT_JR]     = proc_jr,
    [IT_RRA]    = proc_rra,
    [IT_DAA]    = proc_daa,
    [IT_CPL]    = proc_cpl,
    [IT_SCF]    = proc_scf,
    [IT_CCF]    = proc_ccf,
    [IT_HALT]   = proc_halt,
    [IT_ADC]    = proc_adc,
    [IT_SUB]    = proc_sub,
    [IT_SBC]    = proc_sbc,
    [IT_AND]    = proc_and,
    [IT_XOR]    = proc_xor,
    [IT_OR]     = proc_or,
    [IT_CP]     = proc_cp,
    [IT_RET]    = proc_ret,
    [IT_POP]    = proc_pop,
    [IT_JP]     = proc_jp,
    [IT_CB]     = proc_cb,
    [IT_CALL]   = proc_call,
    [IT_PUSH]   = proc_push,
    [IT_RST]    = proc_rst,
    [IT_RETI]   = proc_reti,
    [IT_DI]     = proc_di,
    [IT_EI]     = proc_ei,
    [IT_LDH]    = proc_ldh,
    [IT_JPHL]   = proc_jphl,
    [IT_ERR]    = proc_err,
    // CB instructions
    [IT_RLC]    = proc_rlc,
    [IT_RRC]    = proc_rrc,
    [IT_RL]     = proc_rl,
    [IT_RR]     = proc_rr,
    [IT_SLA]    = proc_sla,
    [IT_SRA]    = proc_sra,
    [IT_SWAP]   = proc_swap,
    [IT_SRL]    = proc_srl,
    [IT_BIT]    = proc_bit,
    [IT_RES]    = proc_res,
    [IT_SET]    = proc_set,
};

IN_PROC inst_get_processor(instruction_type type) {
    return processors[type];
}
