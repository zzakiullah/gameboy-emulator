/**
 * common.h
 * Common macros
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BIT_GET(a, n) ((a & (1 << n)) ? 1 : 0)
#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n); }

#define BETWEEN(a, b, c) ((a >= b) && (a <= c))

#define NO_IMPL { fprintf(stderr, "NOT YET IMPLEMENTED\n"); exit(-5); }
