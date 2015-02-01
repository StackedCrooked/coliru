#include <string>
 
int main()
{
    //no need to write 'using namespace std::literals::string_literals'
    using namespace std::string_literals;
 
    std::string s2 = "abc\0\0def"; // forms the string "abc"
    std::string s1 = "abc\0\0def"s; // form the string "abc\0\0def"
}