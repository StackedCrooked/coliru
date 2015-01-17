/* crack2dx.c: Descramble a .2DX (sound archive) file */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned char byte;

const byte keys_09[] = {
    0x97, 0x1E, 0x24, 0xA0, 0x9A, 0x00, 0x10, 0x2B,
    0x91, 0xEF, 0xD7, 0x7A, 0xCD, 0x11, 0xAF, 0xAF,
    0x8D, 0x26, 0x5D, 0xBB, 0xE0, 0xC6, 0x1B, 0x2B
};

const byte keys_10[] = {
    0x2D, 0x86, 0x56, 0x62, 0xD7, 0xFD, 0xCA, 0xA4,
    0xB3, 0x24, 0x60, 0x26, 0x24, 0x81, 0xDB, 0xC2,
    0x57, 0xB1, 0x74, 0x6F, 0xA7, 0x52, 0x99, 0x21
};

const byte keys_11[] = {
    0xED, 0xF0, 0x9C, 0x90, 0x44, 0x1A, 0x5A, 0x03,
    0xAB, 0x07, 0xC1, 0x99, 0x23, 0x24, 0x32, 0xC7,
    0x5F, 0x32, 0xA5, 0x97, 0xAD, 0x98, 0x0F, 0x8F
};

const byte keys_16[] = {
    0x28, 0x22, 0x28, 0x54, 0x63, 0x3F, 0x0E, 0x42,
    0x6F, 0x45, 0x4E, 0x50, 0x67, 0x53, 0x61, 0x7C,
    0x04, 0x46, 0x00, 0x3B, 0x13, 0x2B, 0x45, 0x6A
};

/** :gonk: */
static void mix(byte block[8])
{
    byte a = block[0] * 63;
    byte b = a + block[3];
    byte c = block[1] * 17;
    byte d = c + block[2];
    byte e = d + b;
    byte f = e * block[3];
    byte g = f + b + 51;
    byte h = b ^ d;
    byte i = g ^ e;

    block[4] ^= h;
    block[5] ^= d;
    block[6] ^= i;
    block[7] ^= g;
}

/** Descrambling loop */
static void descramble(FILE *in, FILE *out, const byte key[24], int full)
{
    byte prev_sblock[8];
    byte cur_sblock[8];
    byte block[8];
    byte tmp;
    int i;

    while (!feof(in)) {
        fread(block, 8, 1, in);
        memcpy(cur_sblock, block, 8);

        for (i = 0 ; i < 8 ; i++) block[i] ^= key[i];
        mix(block);

        for (i = 0 ; i < 4 ; i++) {
            tmp = block[i];
            block[i] = block[i + 4];
            block[i + 4] = tmp;
        }

        if (full) {
            for (i = 0 ; i < 8 ; i++) block[i] ^= key[8 + i];
            mix(block);

            for (i = 0 ; i < 8 ; i++) block[i] ^= key[16 + i];
        }

        for (i = 0 ; i < 8 ; i++) {
            block[i] ^= prev_sblock[i];
        }

        memcpy(prev_sblock, cur_sblock, 8);
        fwrite(block, 8, 1, out);
    }
}

/** Entry point */
int main(int argc, char **argv)
{
    byte hdr[8];
    FILE *out;
    FILE *in;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    in = fopen(argv[1], "rb");
    if (!in) {
        fprintf(stderr, "%s: Could not open file for input\n", argv[1]);
        return EXIT_FAILURE;
    }

    out = fopen(argv[2], "wb");
    if (!out) {
        fprintf(stderr, "%s: Could not open file for output\n", argv[2]);
        return EXIT_FAILURE;
    }

    fread(hdr, 8, 1, in);
    if (memcmp(hdr, "%eNc", 4) == 0) {
        descramble(in, out, keys_09, 1);

    } else if (memcmp(hdr, "%e10", 4) == 0) {
        descramble(in, out, keys_10, 1);

    } else if (memcmp(hdr, "%e11", 4) == 0) {
        descramble(in, out, keys_11, 1);

    } else if (memcmp(hdr, "%e12", 4) == 0 || memcmp(hdr, "%hid", 4) == 0) {
        descramble(in, out, keys_11, 0);

    } else if (memcmp(hdr, "%iO0", 4) == 0) {
        descramble(in, out, keys_16, 1);

    } else {
        fprintf(stderr,
            "Unknown scrambling type, probably not a scrambled file.\n");
        return EXIT_FAILURE;
    }

    fclose(out);
    fclose(in);
    return EXIT_SUCCESS;
}

