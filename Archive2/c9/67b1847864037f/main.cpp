#include <cstdint>
#include <climits>

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <random>


#define BITS(x) (sizeof(x) * CHAR_BIT)
#define ROTL(x, c) ( ((x) << (c)) | ((x) >> (BITS(x) - (c))) )
#define ROTR(x, c) ( ((x) >> (c)) | ((x) << (BITS(x) - (c))) )

#define R0  1
#define R1  4
#define R2  5
#define R3  7

/* The nonlinear primitive */
#define U(A, B) ( ( (A) ^ (B) ) ^ ( ( (A) & (B) ) << 1) )

/* The quarter-round */
#define G(A, B, C, D)                               \
do                                                  \
{                                                   \
    (A) = U(A, B); (D) ^= (A); (D) = ROTR((D), R0); \
    (C) = U(C, D); (B) ^= (C); (B) = ROTR((B), R1); \
    (A) = U(A, B); (D) ^= (A); (D) = ROTR((D), R2); \
    (C) = U(C, D); (B) ^= (C); (B) = ROTR((B), R3); \
} while (0)

static void F(uint8_t S[16])
{
    G(S[ 0], S[ 4], S[ 8], S[12]);
    G(S[ 1], S[ 5], S[ 9], S[13]);
    G(S[ 2], S[ 6], S[10], S[14]);
    G(S[ 3], S[ 7], S[11], S[15]);

    G(S[ 0], S[ 5], S[10], S[15]);
    G(S[ 1], S[ 6], S[11], S[12]);
    G(S[ 2], S[ 7], S[ 8], S[13]);
    G(S[ 3], S[ 4], S[ 9], S[14]);
}

static void f() {
    static std::random_device rd;
    uint8_t S1[16], S2[16];
    uint8_t const D[16] = {
        0x27,0xf9,0xdb,0xc9,
        0x07,0xd2,0xd1,0x10,
        0x7e,0xf5,0xdc,0xc8,
        0xc6,0x92,0x66,0x11
    };
    for(int i = 0; i < 16; ++i) {
        S1[i] = S2[i] = rd();
        S2[i] ^= D[i];
    }
    
    for(int i = 0; i < 2; ++i) {
        F(S1); F(S2);
    }
    for(int i = 0; i < 16; ++i) {
        S1[i] ^= S2[i];
        printf("%02X ", S1[i]);
    }
    printf("\n");
}

int main()
{
    for(int i = 0; i < 10; ++i) {
        f();
    }
}
