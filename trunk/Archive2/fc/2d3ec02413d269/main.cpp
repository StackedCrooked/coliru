#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>
#include <string>
#include <typeinfo>

void Y()
{
   std::cout << "Hello";
}

int X()
{
   Y();
   return 0;
}

int main()
{
   X();
   return 0;
}
