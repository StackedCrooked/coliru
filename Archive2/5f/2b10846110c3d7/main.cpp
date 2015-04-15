#include <iostream>
#include <cmath>

  int FT_FloorFix( int  a )
  {
    return a >= 0 ?   a & ~0xFFFFL
                  : -((-a) & ~0xFFFFL );
  }


int main() {
    std::cout << FT_FloorFix(1)         << " " << std::floor(0.01) << std::endl;
    std::cout << FT_FloorFix(65535)     << " " << std::floor(0.99) << std::endl;
    std::cout << FT_FloorFix(65536)     << " " << std::floor(1.00) << std::endl;
    std::cout << FT_FloorFix(-1)        << " " << std::floor(-0.01) << std::endl;
    std::cout << FT_FloorFix(-65535)    << " " << std::floor(-0.99) << std::endl;
    std::cout << FT_FloorFix(-65536)    << " " << std::floor(-1.00) << std::endl;
}