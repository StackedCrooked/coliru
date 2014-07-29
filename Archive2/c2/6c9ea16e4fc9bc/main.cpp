
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>


int main()
{
   auto nop = [](...) { std::cout << "benfica" << std::endl; };
   using ptr_type = std::unique_ptr<int, decltype(nop)>;
   std::vector<ptr_type> asd;
   asd.push_back(ptr_type(new int(0), nop));
}