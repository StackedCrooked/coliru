#include <iostream>


#define TRACE std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;


namespace foo_default
{    
    void a() { TRACE }
    void b() { TRACE }
}

    
namespace foo_special
{    
    void a() { TRACE }    
    void b() { TRACE }
}


namespace foo
{
    using namespace foo_default;
    using namespace foo_special;
    
    // resolve ambiguities
    using foo_default::a; 
    using foo_special::b;
}


int main()
{
    foo::a();
    foo::b();
}
