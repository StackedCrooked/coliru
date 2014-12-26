#include <cstdint>
#include <cstdio>


struct Byte
{
    template<typename T> Byte& operator=(T t) { puts(__PRETTY_FUNCTION__); return *this; }
    template<typename T> Byte& operator=(const T& t) { puts(__PRETTY_FUNCTION__); return *this; }
};


int main()
{
    Byte b;
    
    int i = 1;
    const int ci = 2;
    
    b = i;  // ambiguous
    b = ci; // ambigous
    
    puts("Done");
}
