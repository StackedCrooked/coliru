#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char* argv[])
{
   assert(argc >= 2);
   const float var = std::stof(argv[1]);
   std::cout << var << '\n';
}
