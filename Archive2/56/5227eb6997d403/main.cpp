#include <iostream>
#include <typeinfo>

struct dummy {};

struct TArg1 {};
struct TArg2 {};
struct TArg3 {};
struct TArg4 {};

void print( )
{}

template<typename THead, typename... TTail> void print( THead head, TTail&... tail )
{
    std::cout << typeid( THead ).name( );
    return print( tail... );
}

template<typename TReq, typename TAns = dummy, typename... TArgs> void foo( TArgs&... args )
{
    std::cout << "TReq: " << typeid( TReq ).name( ) << "; TAns: " << typeid( TAns ).name( ) << std::endl;
    std::cout << "TArgs: ";
    print( args... );
    std::cout << std::endl;
}

int main( )
{
    TArg1 arg1;
    TArg2 arg2;
    TArg3 arg3;
    TArg4 arg4;
    
    foo<TArg1, TArg2>( arg3, arg2 );
    foo<TArg2>( arg1, arg2, arg3, arg4 );
}
