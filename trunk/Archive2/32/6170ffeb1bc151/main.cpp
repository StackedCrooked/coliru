#include <boost/flyweight.hpp>
#include <vector>
#include <iostream>

static void testflyweightString() {
    std::cout << __FUNCTION__ << "\n";
    std::vector<boost::flyweight<std::string> > boost_v;
    for (int i = 0; i < 1000/*0000*/; i++) {
        boost_v.emplace_back("zws_" + std::to_string(i/1000));
    }
}

struct A {
    boost::flyweight<std::string> s;
    A(std::string const& s) : s(s) { }
};

static void testflyweightA() {
    std::cout << __FUNCTION__ << "\n";
    std::vector<A> boost_v;
    for (int i = 0; i < 1000/*0000*/; i++) {
        boost_v.push_back("zws_" + std::to_string(i/1000));
    }
}

int main() {
    testflyweightString();
    testflyweightA();
    std::cout << "Done\n";
}
