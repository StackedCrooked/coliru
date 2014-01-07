#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void print( const char* cstr )
{
    static std::atomic<int> cnt(0) ;

    std::cout << cstr ;
    if( ++cnt%10 == 9 ) std::cout << std::endl ;
    else std::cout << std::flush ;
}

void foo( const char* cstr )
{
    for( int i = 0; i < 20 ; ++i )
    {
        print(cstr) ;
        std::this_thread::sleep_for( std::chrono::milliseconds(1) ) ;
    }
}

int main()
{
    const char* const strings[] = { "foo ", "bar ", "baz ", "FOO ", "BAR ", "BAZ " } ;

    for( auto cstr : strings )
    {
        std::thread t( foo, cstr ) ;
        t.detach() ;

        print( "main " ) ;

        std::this_thread::sleep_for( std::chrono::milliseconds(2) ) ;
    }

    print( "sleeping for a long period... " ) ;
    std::this_thread::sleep_for( std::chrono::seconds(1) ) ;
    print( "done!" ) ;
}
