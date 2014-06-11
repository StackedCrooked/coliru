#include <iostream>
#include <cmath>

using namespace std;

int main()
{  
   int* fuck_you = reinterpret_cast<int*>(0x0);
  
   *fuck_you = 0xDEAD;
   
   return 0;
}
