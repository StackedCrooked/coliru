
#include <iostream>

struct A {
    void Func( int ) {};
    template<class T> void FuncT( T ) {};
};

struct B :A {};
struct C {};

struct YesType {char v[1];};
struct NoType {char v[2];};

template< class SIG, SIG sig > struct Sfinae;
template< class T2 > static YesType Test( Sfinae< void (T2::*)(int), &T2::Func >* );
template< class T2 > static NoType  Test( ... );
template< class T2 > static YesType TestT( Sfinae< void (T2::*)(int), &T2::FuncT >* );
template< class T2 > static NoType  TestT( ... );

template< class T >
struct Check
{
    static const bool value = sizeof(Test<T>(0))==sizeof(YesType);
    static const bool valueT = sizeof(TestT<T>(0))==sizeof(YesType);
};

int main(int argc, char* argv[])
{
    // gives "A=1 B=0 C=0"
    std::cout << "A=" << Check<A>::value << " B=" << Check<B>::value << " C=" << Check<C>::value << std::endl;
    // want same output with FuncT, but doesn't compile:
    // error: ‘&A::FuncT’ is not a valid template argument for type ‘void (B::*)(int)’ because it is of type ‘void (A::*)(int)’
    std::cout << "B=" << Check<B>::valueT << std::endl;
    return 0;
}
