#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  char haslo[10];

  printf("Podaj hasło:");
  scanf("%s", haslo);
  if (strcmp(haslo,"tajne") != 0)
    return 1;
  printf("Ok\n");
  return 0;
}