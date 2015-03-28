#include <iostream>
#include <cstring>
#include <memory>
 
int main()
{
    const char* src = "Take the test.";
//  src[0] = 'M'; // can't modify string literal
    auto dst = std::make_unique<char[]>(std::strlen(src)+1); // +1 for the null terminator
    std::strcpy(dst.get(), src);
    dst[0] = 'M';
    std::cout << src << '\n' << dst.get() << '\n';
}