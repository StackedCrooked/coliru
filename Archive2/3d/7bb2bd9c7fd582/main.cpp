#include <iostream>
#include <vector>
#include <algorithm>

// A type that contains a dynamically allocated list of ints.
class Foo
{
public:
    // Default c'tor 
    Foo( )
    {
        m_instanceId = ++InstanceCounter;
        
        std::cout << "Object # " << m_instanceId << " : Default c'tor called" << std::endl;
    }
    
    // Initializer_list c'tor
    Foo( std::initializer_list<int> list )
        : Foo( ) // Delegate to default c'tor
    {
        m_pValues = new int[list.size( )];
        m_length  = list.size( );
        
        std::copy( list.begin( ), list.end( ), m_pValues );
        
        std::cout << "Object # " << m_instanceId << " : Initializer_list c'tor called" << std::endl;
    }
    
    // Rvalue move c'tor
    Foo( Foo&& other )
        : Foo( ) // Delegate to default c'tor
    {
        // Shallow copy the rvalue's members
        // Stealing the pointer is cheaper than copying the array
        m_pValues       = other.m_pValues;
        m_length        = other.m_length;
        
        // Clear the rvalue
        other.m_pValues = nullptr;
        other.m_length  = 0;
        
        std::cout << "Object # " << m_instanceId << " : Rvalue c'tor called with argument = Object # "<< other.m_instanceId << std::endl;
    }
    
    // Rvalue assignment operator
    Foo& operator=(Foo&& other)
    {
        // Shallow copy the rvalue's members
        // Stealing the pointer is cheaper than copying the array
        m_pValues       = other.m_pValues;
        m_length        = other.m_length;
        
        // Clear the rvalue
        other.m_pValues = nullptr;
        other.m_length  = 0;
        
        std::cout << "Object # " << m_instanceId << " : rvalue assignment operator called with argument = Object # "<< other.m_instanceId << std::endl;
        return *this;
    }
    
    // D'tor
    ~Foo( )
    {
        std::cout << "Object # " << m_instanceId << " : Destructor called - m_pValues member is " << ( m_pValues == nullptr ? "null" : "not null" ) << ")" << std::endl;
        
        delete [] m_pValues;
    }
    
    // Copy and assignment not allowed
    Foo( const Foo& ) = delete;
    Foo& operator=( const Foo& ) = delete;
    
    // Print list of ints to stdout 
    void PrintValues( )
    {
        std::cout << "{ ";
        if ( m_pValues == nullptr )
        {
            std::cout << "null ";
        }
        else
        {
            // Use a lambda to stream out each value
            std::for_each( m_pValues, m_pValues + m_length,
                [] (int value) { std::cout << value << ", "; });
        }
        std::cout << "}" << std::endl;
    }
    
private:
    // Inline member initialization
    int     m_instanceId = 0;
    int*    m_pValues    = nullptr;
    size_t  m_length     = 0;
    
    static int InstanceCounter;
};

int Foo::InstanceCounter = 0; // Can't do inline initialization of statics

// A factory method for Foo
Foo FooFactory( )
{
    // Compiler infers the return type of this rvalue
    // Uses uniform initialization
    return { 1, 2, 3, 4, 5 };
}

int main()
{
    // Construct a default Foo
    Foo foo;
    
    // Should have no values
    foo.PrintValues( );
    
    // Now assign it the value of a new Foo
    foo = FooFactory( ); // The rvalue is created, cloned, and then destroyed on this line
    
    // Now has the values of the rvalue
    foo.PrintValues( );
}
