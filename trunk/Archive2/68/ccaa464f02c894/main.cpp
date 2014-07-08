#include <boost/shared_ptr.hpp>
#include <iostream>
#include <cassert>

struct Foo {
    Foo(int i) : i(i) {}
    ~Foo() { 
        std::cout << __PRETTY_FUNCTION__ << ": " 
            << std::hex << i << std::endl; 
    }
    int i;
};

int main() {
    Foo* pf = new Foo(0x42);
    boost::shared_ptr<Foo> spf1(pf);
    boost::shared_ptr<Foo> spf2(pf);
    assert(spf1.use_count() == 1 && spf2.use_count() == 1);
}