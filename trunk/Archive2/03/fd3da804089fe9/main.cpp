#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct print_type;

int main()
{
   char abc[11] = "abcdefghjk";
   print_type<decltype(&abc)> _;
}
