/**
 * cart.c
 * Cartridge
 */

#include "cart.h"

static cart_context ctx;

const char *cart_get_licensee_name() {
    if (ctx.header->new_licensee_code < 0xa5) {
        return LICENSEE_CODES[ctx.header->new_licensee_code];
    }
    return "UNKNOWN";
}

const char *cart_get_type_name() {
    if (ctx.header->type < 0x23) {
        return CART_TYPES[ctx.header->type];
    }
    return "UNKNOWN";
}

bool cart_load(char *cart) {
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    FILE *fp = fopen(cart, "r");

    if (!fp) {
        printf("Failed to open: %s\n", cart);
        return false;
    }

    printf("Opened: %s\n", ctx.filename);

    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);

    rewind(fp);

    ctx.rom_data = malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    ctx.header = (cart_header *)(ctx.rom_data + 0x100);
    ctx.header->title[15] = 0;

    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", ctx.header->title);
    printf("\t Type     : %2.2X (%s)\n", ctx.header->type, cart_get_type_name());
    printf("\t ROM Size : %d KB\n", 32 << ctx.header->rom_size);
    printf("\t RAM Size : %2.2X\n", ctx.header->ram_size);
    printf("\t LIC Code : %2.2X (%s)\n", ctx.header->new_licensee_code, cart_get_licensee_name());
    printf("\t ROM Vers : %2.2X\n", ctx.header->mask_rom_version_num);

    uint16_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014c; address++) {
        checksum = checksum - ctx.rom_data[address] - 1;
    }

    printf("\t Checksum : %2.2X (%s)\n", ctx.header->checksum, (checksum & 0xff) ? "PASSED" : "FAILED");

    return true;
}
