/**
 * cpu_util.c
 * Utility functions for the CPU
 */

#include "cpu.h"

extern cpu_context ctx;

uint16_t reverse(uint16_t n) {
    // Take low byte and shift it to the left
    // Take high byte and shift it to the right
    // OR them together
    return ((n & 0xff00) >> 8) | ((n & 0x00ff) << 8);
}

uint16_t cpu_read_register(register_type rt) {
    switch (rt) {
        case RT_A:  return ctx.registers.a;
        case RT_F:  return ctx.registers.f;
        case RT_B:  return ctx.registers.b;
        case RT_C:  return ctx.registers.c;
        case RT_D:  return ctx.registers.d;
        case RT_E:  return ctx.registers.e;
        case RT_H:  return ctx.registers.h;
        case RT_L:  return ctx.registers.l;

        case RT_AF: return reverse(*((uint16_t *)&ctx.registers.a));
        case RT_BC: return reverse(*((uint16_t *)&ctx.registers.b));
        case RT_DE: return reverse(*((uint16_t *)&ctx.registers.d));
        case RT_HL: return reverse(*((uint16_t *)&ctx.registers.h));

        case RT_PC: return ctx.registers.pc;
        case RT_SP: return ctx.registers.sp;

        default:    return 0;
    }
}

void cpu_set_register(register_type rt, uint16_t val) {
    switch (rt) {
        case RT_A:
            ctx.registers.a = val & 0xff;
            return;
        case RT_F:
            ctx.registers.f = val & 0xff;
            return;
        case RT_B:
            ctx.registers.b = val & 0xff;
            return;
        case RT_C:
            ctx.registers.c = val & 0xff;
            return;
        case RT_D:
            ctx.registers.d = val & 0xff;
            return;
        case RT_E:
            ctx.registers.e = val & 0xff;
            return;
        case RT_H:
            ctx.registers.h = val & 0xff;
            return;
        case RT_L:
            ctx.registers.l = val & 0xff;
            return;
        case RT_AF:
            *((uint16_t *)&ctx.registers.a) = reverse(val);
            return;
        case RT_BC:
            *((uint16_t *)&ctx.registers.b) = reverse(val);
            return;
        case RT_DE:
            *((uint16_t *)&ctx.registers.d) = reverse(val);
            return;
        case RT_HL:
            *((uint16_t *)&ctx.registers.h) = reverse(val); 
            return;
        case RT_PC:
            ctx.registers.pc = val;
            return;
        case RT_SP:
            ctx.registers.sp = val;
            return;
        case RT_NONE:
        default:
            return;
    }
}
