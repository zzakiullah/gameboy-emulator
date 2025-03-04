/**
 * cart.h
 * Cartridge
 */

#pragma once

#include "common.h"

typedef struct {
    uint32_t    entry;
    uint8_t     logo[0x30];
    char        title[16];
    uint16_t    new_licensee_code;
    uint8_t     sgb_flag;
    uint8_t     type;
    uint8_t     rom_size;
    uint8_t     ram_size;
    uint8_t     destination_code;
    uint8_t     old_licensee_code;
    uint8_t     mask_rom_version_num;
    uint8_t     checksum;
    uint16_t    global_checksum;
} cart_header;

typedef struct {
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
    cart_header *header;
} cart_context;

const char *cart_get_licensee_name();
const char *cart_get_type_name();
bool cart_load(char *cart);
uint8_t cart_read(uint16_t address);
void cart_write(uint16_t address, uint8_t value);
