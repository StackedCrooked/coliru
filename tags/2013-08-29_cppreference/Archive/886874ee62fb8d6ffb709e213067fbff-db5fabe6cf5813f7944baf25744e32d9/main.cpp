
#include <iostream>

struct A { template< class T > void Func( int ) {}; };
struct B :A {};

template< class T >
struct CheckForFunc
{
    template< class U, void (U::*)(int) > struct Sfinae;
    template< class T2 > static char (&Test( ... ))[1];
    template< class T2 > static char (&Test( Sfinae<T2,&T2::Func>* ))[2];
    static const bool value = sizeof(Test<T>(0))==sizeof(char[2]);
};

int main(int argc, char* argv[])
{
    std::cout << "Value A=" << CheckForFunc< A >::value << std::endl;
    std::cout << "Value B=" << CheckForFunc< B >::value << std::endl;
    return 0;
}