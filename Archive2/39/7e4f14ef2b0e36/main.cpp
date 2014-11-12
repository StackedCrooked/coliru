#include <stdio.h>

int main() {

  struct birthyear {
      int birth;
  };

  struct person {
      int age;
      char forename[5];
      struct birthyear pbirthyear;
  };

  struct person p1;
  int age = 45;

  printf("%zu", sizeof(struct birthyear));
  printf(" %zu", sizeof(p1.pbirthyear));
  printf(" %zu", sizeof(age));
  return 0;
}