#include <iostream>
#include <cstddef>

template<typename T> void f(const char*) //#1
{ 
    std::cout << "f(const char*)\n"; 
}

template<typename T, std::size_t N> void f(const char(&)[N]) //#2
{ 
    std::cout << "f(const char (&)[N])\n"; 
}

int main()
{
    f<int>("ab");
}