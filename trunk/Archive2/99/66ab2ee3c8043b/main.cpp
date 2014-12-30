#define BOOST_VARIANT_MINIMIZE_SIZE
#include <boost/variant.hpp>

using init = boost::variant<long long, char const*, wchar_t const*>;

#include <iostream>

int main() {
    init initial_data [] = {
        init { 3 },      // initializes x, brace elision
        init { "foo" },  // initializes s 
        init { L"Foo" }  // initializes w
    };

    for(auto& v : initial_data)
        std::cout << v.which() << "\t" << v << "\n";
}
