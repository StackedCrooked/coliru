#include <stdio.h>

int choose_random_number(int n);

int main() {
  int player_x = 10, player_y = 10;
  printf("player position: %d %d\n", player_x, player_y);

  for (int i = 0; i < 100; ++i) { // simulate 100 steps

    // No obstructions, so the player can always move in any of the four
    // cardinal directions
    int number_of_choices = 4;
    int choice = choose_random_number(number_of_choices);
    // apply the choice
    // up is 0, right is 1, down is 2, left is 3
    switch (choice) {
    case 0: --player_y; puts("Up"); break;
    case 1: ++player_x; puts("Right"); break;
    case 2: ++player_y; puts("Down"); break;
    case 3: --player_x; puts("Left"); break;
    }

    printf("player position: %d %d\n", player_x, player_y);
  }
}

#include <stdint.h>
#include <assert.h>

// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;

uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

int choose_random_number(int n) {
  assert(0 < n);

  static pcg32_random_t state = {0};
  uint32_t max = UINT32_MAX - (UINT32_MAX + 1ull) % n;
  uint32_t m;
  do {
    m = pcg32_random_r(&state);
  } while (m > max);
  return m % n;
}

