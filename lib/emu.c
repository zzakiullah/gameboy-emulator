/**
 * emu.c
 * Emulator
 * 
 * Components:
 *  - Cart
 *  - CPU
 *  - Address bus
 *  - PPU
 *  - Timer
 */

#include "emu.h"
#include "cart.h"
#include "cpu.h"

static emu_context ctx;

emu_context *emu_get_context() {
    return &ctx;
}

int emu_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded.\n");

    cpu_init();
    
    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while (ctx.running) {
        if (ctx.paused) {
            // Delay for some number of milliseconds
            continue;
        }

        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return -3;
        }

        ctx.ticks++;
    }

    return 0;
}
