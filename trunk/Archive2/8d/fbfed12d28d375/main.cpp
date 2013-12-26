#include <cstdio>

bool passMin(float val, float minval=10.) {return minval<val;}

int main () {
  float val(20.0), minval(25.0);
  if(passMin(val), minval) printf(" pass (p( ), )"); else printf(" fail (p( ), )");
  printf("\n");
  if(passMin(val, minval)) printf(" pass (p( , ))"); else printf(" fail (p( , ))");
  printf("\n");
}