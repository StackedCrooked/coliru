#include <cstdint>  // for std::uint_fast8_t
#include <array>
#include <string>
#include <iostream>

enum class MyEnum : std::uint_fast8_t {
   AAA,
   BBB,
   CCC,
};

std::array<std::string,3> MyEnumStrings { 
   "AAA", 
   "BBB", 
   "CCC"
};

int main()
{
   std::cout << MyEnumStrings[ static_cast<std::size_t>(MyEnum::AAA) ] <<'\n';
}
