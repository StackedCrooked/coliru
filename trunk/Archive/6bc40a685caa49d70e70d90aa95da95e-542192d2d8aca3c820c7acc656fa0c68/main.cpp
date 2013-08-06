
#include <iostream>
#include <utility>

struct A { template<class T> void Func( T ) {}; };

struct B : A {};

struct C {};

template< class T >
struct CheckForFunc
{
    typedef char(&YesType)[1];
    typedef char(&NoType)[2];
    template< class, class > struct Sfinae;

    template< class T2 > static YesType Test( Sfinae<T2, decltype(std::declval<T2>().Func(0))> * );
    template< class T2 > static NoType  Test( ... );
    static const bool value = sizeof(Test<T>(0))==sizeof(YesType);
};

int main(int argc, char* argv[])
{
    std::cout << "Value A=" << CheckForFunc< A >::value << std::endl;
    std::cout << "Value B=" << CheckForFunc< B >::value << std::endl;
    std::cout << "Value C=" << CheckForFunc< C >::value << std::endl;
    return 0;
}