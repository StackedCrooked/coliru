#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>

struct Thing : boost::enable_shared_from_this<Thing> {};

void deleter(Thing * t) {std::cout << "Deleting\n"; delete t;}

int main() {
    boost::shared_ptr<Thing> p1(new Thing, deleter);
    boost::shared_ptr<Thing> p2(p1->shared_from_this());

    std::cout << "Release first\n";
    p1.reset();
    std::cout << "Release second\n";
    p2.reset();
}
