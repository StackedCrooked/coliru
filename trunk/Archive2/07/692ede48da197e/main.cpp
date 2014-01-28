#include <string>
using namespace std::string_literals;
 
int main()
{
    std::string s2 = "abc\0\0def"; // forms the string "abc"
    std::string s1 = "abc\0\0def"s; // form the string "abc\0\0def"
}