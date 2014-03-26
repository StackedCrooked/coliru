// Type your code here, or load an example.
#include <string>
#include <iostream>

#include <cstdlib>

class FooBar
{
public:
    FooBar( )
        : m_foo( "Foo" )
    {
    }

    const std::string& GetStringRef( )
    {
        return m_foo;
    }

    std::string GetStringCopy( )
    {
        return "Bar";
    }
    
    std::string m_foo;
};

const std::string& GeneratesCompilerWarning( )
{
    return "Whoops, I shouldn't do this";
}

int main( )
{
    const std::string& foo = FooBar( ).GetStringRef( ); // A
    const std::string& bar = FooBar( ).GetStringCopy( ); // B

    std::cout << "Hello World: " << foo << std::endl;
    std::cout << "Hello World: " << bar << std::endl;
}