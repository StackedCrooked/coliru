#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <iostream>

struct foo
{
    foo() { std::cout << "ctor\n"; }
    ~foo() { std::cout << "dtor\n"; }
};

int main()
{
    boost::shared_ptr<foo> f = boost::make_shared<foo>();
    boost::shared_ptr<void> v( f, f.get() );
    
    std::cout << "before reset\n";
    f.reset();
    std::cout << "after reset\n";
}