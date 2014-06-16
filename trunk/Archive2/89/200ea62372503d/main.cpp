#include <iostream>
#include <string>

using namespace std::literals;

int main()
{
   auto a = "2300"s;

   auto b = [](auto d) {
      auto t = std::stoull(d);
      return t / 2.300;
   };

   std::cout << b(a) << '\n';
}
