#include <stdio.h>
#include <math.h>

int roundUpto2digit(int cents) {
  if (cents < 100)
    return cents < 10 ? cents * 10 : cents;
  while ((cents + 5) >= 1000)
    cents /= 10;
  return (cents + 5) / 10;
}

int roundUpto2digit2(int cents) {
    double lg10 = log10(cents);
    double frac = lg10 - floor(lg10); 
    return (int) round(10 * pow(10, frac));
}

void
test(int i) {
    int v1 = roundUpto2digit(i);
    int v2 = roundUpto2digit2(i);
    printf("%d -> %d / %d: %s\n", i, v1, v2, v1 == v2 ? "pass" : "fail !!!");
}

int
main() {
    test(0);
    test(1);
    test(5);
    test(9);
    test(10);
    test(49);
    test(50);
    test(94);
    test(95);
    test(99);
    test(100);
    test(104);
    test(105);
    test(994);
    test(995);
    test(999);
    test(1000);
    test(1040);
    test(1050);
    return 0;
}