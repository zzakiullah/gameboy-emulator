/**
 * emu.h
 * Emulator
 */

#pragma once

#include "common.h"

typedef struct {
    bool paused;
    bool running;
    uint64_t ticks;
} emu_context;

emu_context *emu_get_context();
int emu_run(int argc, char **argv);
