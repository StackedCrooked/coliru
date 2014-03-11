#include <iostream>

using namespace std;

void stars(int n) {
  for (int i = 0; i < n; ++i) {
    printf("*");
  }
  printf("\n");
}

int main()
{
   stars(2);
   stars(10);
   stars(6);
   stars(2);
   stars(2);
   
   return 0;
}
