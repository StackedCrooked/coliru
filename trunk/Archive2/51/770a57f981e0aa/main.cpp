#include <stdlib.h>
#include <stdio.h>

struct abc {
  void *test;
};

struct def {
  int a;
  int b;
};

struct abc*
abc_init(int sz) {
  struct abc *out = (abc*) malloc(sizeof(abc));
  out->test       = malloc(sz);
  return out;
}

void
abc_finit(struct abc *in) {
  if(in) {
    if(in->test) free(in->test);
    free(in);
  }
}

int main() {
  abc *mystruct = abc_init(sizeof(def));
  ((def*)(mystruct->test))->a = 3;
  printf("%d\n", static_cast<def*>(mystruct->test)->a);
  abc_finit(mystruct);
    
  return 0;
}