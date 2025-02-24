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

const char *LICENSEE_CODES[0xa5] = {
    [0x00] = "None",
    [0x01] = "Nintendo Research & Development 1",
    [0x08] = "Capcom",
    [0x13] = "EA (Electronic Arts)",
    [0x18] = "Hudson Soft",
    [0x19] = "B-AI",
    [0x20] = "KSS",
    [0x22] = "Planning Office WADA",
    [0x24] = "PCM Complete",
    [0x25] = "San-X",
    [0x28] = "Kemco",
    [0x29] = "SETA Corporation",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean Software/Acclaim Entertainment",
    [0x34] = "Konami",
    [0x35] = "HectorSoft",
    [0x37] = "Taito",
    [0x38] = "Hudson Soft",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu Interactive",
    [0x46] = "Angel",
    [0x47] = "Bullet-Proof Software",
    [0x49] = "Irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim Entertainment",
    [0x52] = "Activision",
    [0x53] = "Sammy USA Corporation",
    [0x54] = "Konami",
    [0x55] = "Hi Tech Expressions",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley Company",
    [0x60] = "Titus Interactive",
    [0x61] = "Virgin Games Ltd.",
    [0x64] = "Lucasfilm Games",
    [0x67] = "Ocean Software",
    [0x69] = "EA (Electronic Artss)",
    [0x70] = "Infogrames",
    [0x71] = "Interplay Entertainment",
    [0x72] = "Broderbund",
    [0x73] = "Sculptured Software",
    [0x75] = "The Sales Curve Limited",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "Misawa Entertainment",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft Co.",
    [0x92] = "Video System",
    [0x93] = "Ocean Software/Acclaim Entertainment",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s'pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack-In-Video",
    // [9H] = "Bottom Up"
    [0xa4] = "Konami (Yu-Gi-Oh!)",
    // [BL] = "MTO"
    // [DK] = "Kodansha"
};

const char *CART_TYPES[] = {
    [0x00] = "ROM_ONLY",
    [0x01] = "MBC1",
    [0x02] = "MBC1+RAM",
    [0x03] = "MBC1+RAM+BATTERY",
    [0x05] = "MBC2",
    [0x06] = "MBC2+BATTERY",
    [0x08] = "ROM+RAM",
    [0x09] = "ROM+RAM+BATTERY",
    [0x0b] = "MMM01",
    [0x0c] = "MMM01+RAM",
    [0x0d] = "MMM01+RAM+BATTERY",
    [0x0f] = "MBC3+TIMER+BATTERY",
    [0x10] = "MBC3+TIMER+RAM+BATTERY",
    [0x11] = "MBC3",
    [0x12] = "MBC3+RAM",
    [0x13] = "MBC3+RAM+BATTERY",
    [0x19] = "MBC5",
    [0x1a] = "MBC5+RAM",
    [0x1b] = "MBC5+RAM+BATTERY",
    [0x1c] = "MBC5+RUMBLE",
    [0x1d] = "MBC5+RUMBLE+RAM",
    [0x1e] = "MBC5+RUMBLE+RAM+BATTERY",
    [0x20] = "MBC6",
    [0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    // [0xfc] = "POCKET CAMERA",
    // [0xfd] = "BANDAI TAMA5",
    // [0xfe] = "HuC3",
    // [0xff] = "HuC1+RAM+BATTERY",
};

const char *cart_get_licensee_name();
const char *cart_get_type_name();
bool cart_load(char *cart);
