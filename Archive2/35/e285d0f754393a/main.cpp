#include <vector>
#include <stdio.h>

int comp(long long i) {
  static std::vector<int> collatz(4000000);
  collatz[1] = 1;
  if (i>=collatz.size())
      return 1 + comp(i&1 ? 3*i+1 : i/2);
  if(!collatz[i])
      collatz[i] = 1 + comp(i&1 ? 3*i+1 : i/2);
  return collatz[i];
}

int main() {
  int highNumber= 1, highCount = 1, c;
  for(int i = 2; i < 1000000; i++)
    if((c = comp(i)) > highCount) {
      highCount = c;
      highNumber = i;
    }
  printf( "The number with the highest count: %d with the count of %d\n",
        highNumber, highCount );
}
