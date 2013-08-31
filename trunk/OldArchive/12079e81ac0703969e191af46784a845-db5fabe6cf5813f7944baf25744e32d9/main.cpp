#include <iostream>

struct A { enum { IsTagged }; struct IsTaggedStruct{}; };
struct B :A {};
struct C {};

template< int > struct HasTag;

template< class TST >
struct Check
{
    template< class T2 > static char (&Test( ... ))[1];
    template< class T2 > static char (&Test( HasTag<T2::IsTagged>* ))[2];
    //template< class T2 > static char (&Test( typename T2::IsTaggedStruct* ))[2];
    static const bool value = sizeof(Test<TST>(0))==sizeof(char[2]);
};

int main(int argc, char* argv[])
{
    std::cout << "Value A=" << Check< A >::value << std::endl;
    std::cout << "Value B=" << Check< B >::value << std::endl;
    std::cout << "Value C=" << Check< C >::value << std::endl;
    return 0;
}