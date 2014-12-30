#define BOOST_VARIANT_MINIMIZE_SIZE
#include <boost/variant.hpp>

using init = boost::variant<long long, char const*, wchar_t const*>;

#include <iostream>

int main() {
    init initial_data [] = {
        3 ,      // initializes x, brace elision
        "foo" ,  // initializes s 
        L"Foo"   // initializes w
    };

    for(auto& v : initial_data)
        std::cout << v.which() << "\t" << v << "\n";
}
