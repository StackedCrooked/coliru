
#include <iostream>
#include <string>

std::string operator * (std::string const & s, size_t n)
{
   std::string result;
   while(n--) result += s;
   return result;
}
std::string operator"" _s(char const *str, size_t ) //User-defined string literal
{
    return str;
}
void printxy(size_t n)
{
    std::cout << "XY"_s * n << std::endl; //repeat pattern n times!
}
int main()
{
    printxy(10);
    printxy(20);
    std::cout << std::string("foo") * 25  << std::endl;
    std::cout << "foo"_s * 15  << std::endl;
}