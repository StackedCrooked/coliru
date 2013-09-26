#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
 
bool isvowel(char c)
{
    return std::string("aeoiuAEIOU").find(c) != std::string::npos;
}
 
int main()
{
    std::string s = "Hello, world!";
    std::copy_if(s.begin(), s.end(), std::ostreambuf_iterator<char>(std::cout),
                 std::not1(std::ptr_fun(isvowel)));
// C++11 alternatives: 
//               std::not1(std::ref(isvowel)));
//               std::not1(std::function<bool(char)>(isvowel)));
 
}