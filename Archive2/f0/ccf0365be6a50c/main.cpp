#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
int main()
{
   std::string str = "e69bb5d83e29083e2c1c025194f2bc9543b4bb0f97cb9a8a0c318bd9ab3b3174";
   boost::to_upper(str);
   std::cout << str << std::endl;
   return 0;
}
