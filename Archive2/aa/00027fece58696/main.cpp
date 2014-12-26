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
    const Byte c;
    
    
    b = b;
    b = c;
    puts("Done");
}
