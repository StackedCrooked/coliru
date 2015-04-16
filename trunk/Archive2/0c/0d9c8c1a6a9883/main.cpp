#include <string>
#include <iostream>
int main()
{
    std::string s = "abc";       // allocation + constructor call
    std::cout << s << '\n';
    s.~basic_string();           // destructor call, no deallocation
    new (&s) std::string("def"); // constructor call, no allocation
    std::cout << s << '\n';
}                                // destructor call + deallocation
