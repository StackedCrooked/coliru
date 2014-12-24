#include <iostream>
#include <vector>

#ifndef __clang__

#include <ext/vstring.h>
using string = __gnu_cxx::__vstring;

#else

#include <string>
using string = std::string;

#endif

int main()
{
    std::cout << sizeof(string("hi")) << " ";
    string a[10];
    std::cout << sizeof(a) << " ";
    std::vector<string> v(10);
    std::cout << sizeof(v) + sizeof(string) * v.capacity() << "\n";
}
