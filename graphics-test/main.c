#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cbm.h>
#include <cx16.h>
#include <string.h>

#define BITMAP_BASE 0x0000
#define PALETTE_OFFSET 0x0
#define VERA_PALETTE_ADDR 0x1FA00

void write_palette(unsigned char index, unsigned char red, unsigned char green, unsigned char blue) {
    unsigned long palette_addr = VERA_PALETTE_ADDR + (index * 2);
    vpoke((green << 4) + blue, palette_addr);
    vpoke(red, palette_addr + 1);
}

int main() {
    clrscr();
    vera_layer_enable(0b01);
    VERA.layer0.config = 0b00000100;
    VERA.layer0.tilebase = (BITMAP_BASE << 2) + 1;
    VERA.layer0.hscroll = (PALETTE_OFFSET << 8);

    // Set up palette
    write_palette(0, 0, 0, 0);
    write_palette(1, 15, 0, 15);

    VERA.data0

    cgetc();
    return 0;
}
