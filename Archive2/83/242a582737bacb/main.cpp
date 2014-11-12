#include <type_traits>
#include <cstddef>
#include <array>
#include <cmath>
#include <iostream>

int main () {
   
   std::cout << -123 % 3 << std::endl;
   std::cout << std::fmod( -123.0, 3.0 ) << std::endl;
   
}