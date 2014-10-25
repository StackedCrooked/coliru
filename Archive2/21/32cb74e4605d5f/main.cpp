#include <stdio.h>
#include <array>

static std::array<short, 1000000> collatz;

static short comp(const int i) {
    short r = collatz[i];
    if(!r) {
        unsigned long long n = i;
        int add = 0;
        do {
            ++add;
            n = n&1 ? 3*n+1 : n/2;
        } while(n>=collatz.size());
        r = add + comp(n);
        collatz[i] = r;
    }
    return r;
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
}
