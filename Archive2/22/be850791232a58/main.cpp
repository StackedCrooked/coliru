#include <stdio.h>
#include <stdlib.h>
#define ROMSIZE 0x200000

static const struct {
  char *name;
  char *revision;
  int rev_mask;
} table[] = {
  { "sfiii"   , ""          , 0x0000 }, // sfiiin
  { "sfiii2"  , ""          , 0x0000 }, // sfiii2n
  { "sfiii3"  , "(__990608)", 0x0003 }, // sfiii3n
  { "sfiii3"  , "(__990512)", 0x0003 }, // sfiii3nr1
  { "jojo"    , "(__990128)", 0x000f }, // jojon
  { "jojo"    , "(__990108)", 0x000f }, // jojonr1
  { "jojo"    , "(__981202)", 0x000f }, // jojonr2
  { "jojoba"  , "(__990927)", 0x000f }, // jojoban, jojobane
  { "jojoba"  , "(__990913)", 0x000f }, // jojobanr1, jojobaner1
  { "redearth", ""          , 0x0000 }, // redearth
};

static int prompt(int max) {
  char str[256];
  int val;

  do {
    printf(">");
    fgets(str, sizeof str, stdin);
    val = atoi(str);
  } while (val < 1 || max < val);

  return val;
}

static int address(int simm, int flash, int offset) {
  if (simm < 4)
    return offset * 4 + flash;
  else if (flash < 2)
    return offset * 2 + flash % 2;
  else
    return offset * 2 + flash % 2 + ROMSIZE * 2;
}

static FILE *open_file(int id, int simm, int flash, char *mode) {
  char filename[32];

  if (id < 0)
    sprintf(filename, "%d%d", simm / 2 + 1, simm % 2);
  else
    sprintf(filename, "%s%s-simm%d.%d", table[id].name, 1 << simm & table[id].rev_mask ? table[id].revision : "", simm / 2 + 1, simm % 2 * 4 + flash);

  return fopen(filename, mode);
}

int main(void) {
  FILE *fp;
  char *buffer;
  int simm, flash, offset, id;

  buffer = (char*)malloc(ROMSIZE * 5);
  if (buffer == NULL)
    return 1;

  printf("ROMSET を選択 :\n");
  for (id = 0; id < sizeof table / sizeof table[0]; id++)
    printf("%2d. %s%s\n", id + 1, table[id].name, table[id].revision);
  id = prompt(id) - 1;

  printf("\n処理を選択 :\n 1. 分割 (旧形式→新形式)\n 2. 結合 (新形式→旧形式)\n");
  if (prompt(2) == 1) {
    // 分割
    for (simm = 12; simm--;) {
      fp = open_file(-1, simm, -1, "rb");
      if (fp == NULL)
        continue;
      flash = fread(buffer + ROMSIZE, ROMSIZE, 4, fp);
      flash = (simm < 4 ? flash / 4 * 4 : flash / 2 * 2);
      fclose(fp);

      for (; flash--;) {
        fp = open_file(id, simm, flash, "wb");
        if (fp == NULL)
          break;
        for (offset = ROMSIZE; offset--;)
          buffer[offset] = buffer[address(simm, flash, offset) + ROMSIZE];
        fwrite(buffer, ROMSIZE, 1, fp);
        fclose(fp);
      }
    }
  }
  else {
    // 結合
    for (simm = 12; simm--;) {
      for (flash = 0; flash < 4; flash++) {
        fp = open_file(id, simm, flash, "rb");
        if (fp == NULL)
          break;
        fread(buffer, ROMSIZE, 1, fp);
        fclose(fp);
        for (offset = ROMSIZE; offset--;)
          buffer[address(simm, flash, offset) + ROMSIZE] = buffer[offset];
      }

      flash = (simm < 4 ? flash / 4 * 4 : flash / 2 * 2);
      if (!flash)
        continue;
      fp = open_file(-1, simm, -1, "wb");
      if (fp == NULL)
        continue;
      fwrite(buffer + ROMSIZE, ROMSIZE, flash, fp);
      fclose(fp);
    }
  }

  free(buffer);
  return 0;
}
