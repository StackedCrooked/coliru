#include <stdio.h>

static int collatz[4000000];
unsigned long long collatzmax;

int comp(unsigned long long i) {
  if(i>=sizeof collatz/sizeof*collatz) {
      if(i>collatzmax)
        collatzmax = i;
      return 1 + comp(i&1 ? 3*i+1 : i/2);
  }
  if(!collatz[i])
      collatz[i] = 1 + comp(i&1 ? 3*i+1 : i/2);
  return collatz[i];
}

int main() {
  collatz[1] = 1;
  int highNumber= 1, highCount = 1, c;
  for(int i = 2; i < 1000000; i++)
    if((c = comp(i)) > highCount) {
      highCount = c;
      highNumber = i;
    }
  printf( "The number with the highest count: %d with the count of %d\n",
        highNumber, highCount );
  printf( "Highest intermediary number: %llu\n", collatzmax);
}
