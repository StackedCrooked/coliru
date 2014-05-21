#include <type_traits>
#include <cstddef>
#include <array>
#include <cmath>
#include <iostream>

int main () {
   
   std::cout << -123 % 2 << std::endl;
   std::cout << std::fmod( -123.0, 2.0 ) << std::endl;
   
}