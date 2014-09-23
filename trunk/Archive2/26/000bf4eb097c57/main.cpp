#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* formResult(char *prefix, char *suffix) {
  printf("step1\n");
  char *result =  malloc(strlen(prefix) + strlen(suffix) + 1);
  result = strcpy(result, prefix);
  result = strcat(result, suffix);
  return result;
}

int main(int argc, char *argv[]) {
  char *prefix = malloc(15), *suffix = malloc(15);
  prefix = strcpy(prefix, "p");
  suffix = strcpy(suffix, "aa");
  char *result /* = malloc(30) */;

  printf("step0\n");
  result = formResult(prefix, suffix);
  printf ("result is %s\n", result);

  return 0;

} 
