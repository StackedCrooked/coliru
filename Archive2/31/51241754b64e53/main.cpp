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

  /* The next two lines show that the addresses are the same. That is what I expected */
  printf("&person.pbirthyear: %p\n", &p1.pbirthyear);
  printf("&person.pbirthyear.birth: %p\n", &p1.pbirthyear.birth);

  p1.pbirthyear = *(struct birthyear *)&age; // This line works
  /* The next line would produce a compiler error: conversion to non-scalar type requested */
  p1.pbirthyear = (struct birthyear) age; 

  printf("%i\n", p1.pbirthyear);
  printf("%i\n", p1.pbirthyear.birth);
  return 0;
}