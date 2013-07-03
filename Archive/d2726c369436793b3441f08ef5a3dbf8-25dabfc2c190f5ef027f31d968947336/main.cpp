#include <boost/variant.hpp>
#include <iostream>

struct visitor : boost::static_visitor<> {
    void operator()(int x) const {
        std::cout << "int " << x << '\n';
    }
    
    void operator()(std::string const& s) const {
        std::cout << "std::string " << s << '\n';
    }
};

int main() {
    boost::variant<int, std::string> variant;
    variant = 42;
    boost::apply_visitor(visitor(), variant);
    variant = "Hello, world!";
    boost::apply_visitor(visitor(), variant);
}
