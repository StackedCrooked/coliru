#include <iostream>
#include <string>
#include <memory>
#include <boost/pool/pool_alloc.hpp>
#include <vector>

struct test
{
    test( std::string a = "default_a", std::string b = "default_b" ) : a(a), b(b)
    { std::cout << "test::test( '" << a << "', " << b << " ) object at: " << this << '\n' ; }

    ~test() { std::cout << "test::~test() object at: " << this << '\n' ; }

    std::string a ;
    std::string b ;
};

int main()
{
    boost::pool_allocator<test> custom_allocator ;

    std::vector< std::shared_ptr<test> > pointers = 
    {
        std::allocate_shared<test>( custom_allocator ),
        std::allocate_shared<test>( custom_allocator, "abcd" ),
        std::allocate_shared<test>( custom_allocator, "efgh", "ijkl" ),
        
        std::make_shared<test>(),
        std::make_shared<test>( "mnop" ),
        std::make_shared<test>( "qrst", "uvwx" ),
        
        std::shared_ptr<test>( new test()) ,
        std::shared_ptr<test>( new test( "yzAB" )) ,
        std::shared_ptr<test>( new test( "CDEF", "GHIJ" ))
    };
        
}
