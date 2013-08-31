#include <iostream>
#include <cstdint>
 
struct MyStruct
{
  union
  {
      int8_t foo[4];
      int32_t bar;
  };
};
 
int main()
{
    struct MyStruct x;
    
    x.bar = 0x12345678;
    for(int i = 0; i < 4; ++i)
        std::cout << (int)x.foo[i]  << ':' << x.foo[i] << std::endl;
}