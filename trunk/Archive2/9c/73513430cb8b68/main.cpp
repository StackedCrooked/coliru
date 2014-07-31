#include <stdio.h>  
struct pair {
  int x;
  int y;
};

int func(pair a, int b) {
  return a.x*b;
}

int func(pair a){
  return func(a, a.y);
}



int main() {
  pair z;
  z.x = 2;
  z.y = 4;
  printf("%d\n", func(z));
  printf("%d\n", func(z,12));
}