#include <boost/variant/variant.hpp>
#include <iostream>

struct foo {};
struct bar {};

void function(boost::variant<foo, bar> val) {std::cout << "success";}

int main() {
    function(foo{});
}

