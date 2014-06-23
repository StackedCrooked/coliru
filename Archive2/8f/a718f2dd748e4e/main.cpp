#include <iostream>
#include <tuple>

template<const char* str>
struct chars
{
    static_assert(false, "");
};

template struct chars<new char>;

int main()
{
    
}