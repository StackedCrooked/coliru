// Type your code here, or load an example.
#include <string>
#include <iostream>
#include <memory>

#include <cstdlib>

class Foo
{
};

Foo SomeFunction( )
{
    return Foo( );
}

void SomeOtherFunctionA( Foo& derived )
{
    std::cout << "Hello world!" << std::endl;
}

void SomeOtherFunctionB( const Foo& derived )
{
    std::cout << "Hello world!" << std::endl;
}

int main( )
{
    // Won't compile because SomeFunction( ) is creating a temporary here
    // and SomeOtherFunctionA takes in a non-const reference
    // SomeOtherFunctionA( SomeFunction( ) );
    
    SomeOtherFunctionB( SomeFunction( ) );
}