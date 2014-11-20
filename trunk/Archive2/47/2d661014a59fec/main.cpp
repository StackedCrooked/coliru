#include <iostream>
#include <string>
#include <vector>

struct bit_st
{
  unsigned char bit_0 : 1;
  unsigned char bit_1 : 1;
  unsigned char bit_2 : 1;
  unsigned char bit_3 : 1;
  unsigned char bit_4 : 1;
  unsigned char bit_5 : 1;
  unsigned char bit_6 : 1;
  unsigned char bit_7 : 1;
};

union mytypes_t {
  bit_st bits;
  unsigned int i;
} mytypes;

int main()
{
    mytypes_t luigi;
    luigi.i = 0x0005;
    std::cout << "luigi I = " << luigi.i << std::endl;
    std::cout << "luigi bit_0 = " << (short)luigi.bits.bit_0 << std::endl;
    std::cout << "luigi bit_1 = " << (short)luigi.bits.bit_1 << std::endl;
    std::cout << "luigi bit_2 = " << (short)luigi.bits.bit_2 << std::endl;
    std::cout << "luigi bit_3 = " << (short)luigi.bits.bit_3 << std::endl;
    std::cout << "luigi bit_4 = " << (short)luigi.bits.bit_4 << std::endl;
    std::cout << "luigi bit_5 = " << (short)luigi.bits.bit_5 << std::endl;
    std::cout << "luigi bit_6 = " << (short)luigi.bits.bit_6 << std::endl;
    std::cout << "luigi bit_7 = " << (short)luigi.bits.bit_7 << std::endl;
}
