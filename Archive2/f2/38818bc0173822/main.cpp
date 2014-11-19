#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  char password[10];

  printf("Give password:");
  scanf("%s", password);
  if (strcmp(password,"secret") != 0)
    return 1;
  printf("Ok\n");
  return 0;
}