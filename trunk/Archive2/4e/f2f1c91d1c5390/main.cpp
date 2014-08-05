#include <iostream>
#include <string>
#include <vector>

class Thread
{
public:
    template <typename F, typename T>
    Thread( F memberFunction, T* instance )
    {
        // Do in boost::thread( boost::bind( ) );
        Run( memberFunction, instance );
    }
    
    template <typename F, typename T>
    void Run( F memberFunction, T* instance )
    {
        // Register thread info
        
        (instance->*memberFunction)( );
    }
};

class Foo
{
public:
    void HelloWorld( )
    {
        std::cout << "Hello world" << std::endl;
    }
};

int main( )
{
    Foo bar;
    
    Thread( &Foo::HelloWorld, &bar );
    
    return 0;
}