#include <cstdint>
#include <cstdio>


struct Byte
{
    template<typename T> Byte& operator=(T t) { puts(__PRETTY_FUNCTION__); return *this; }
    template<typename T> Byte& operator=(T& t) { puts(__PRETTY_FUNCTION__); return *this; }
};


int main()
{
    Byte b;
    b = b;
}
