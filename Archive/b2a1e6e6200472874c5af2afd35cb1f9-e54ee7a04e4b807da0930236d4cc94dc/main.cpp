#include <boost/variant/variant.hpp>
#include <iostream>

struct foo {};
struct bar {};

typedef boost::variant<foo, bar> var;

void function(var val) {std::cout << "success";}

int main() {
    function(foo{});
}

