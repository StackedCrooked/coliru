#include <iostream>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

struct O{
};
struct A:O{
};
struct B:O{
};


int main(int argc, char** argv) {
    boost::variant<A, B> v;
    std::cout << boost::get<A>(&v) << std::endl;
    std::cout << boost::get<O>(&v) << std::endl;
    return 0;
}