#include <iostream>
#include <boost/variant.hpp>
#include <string>

struct Base {};

struct A: Base {};
struct B: Base {};
struct C: Base {};

typedef boost::variant<A, B, C> MyType;

struct MyBehaviour : boost::static_visitor<std::string>
{
    template <typename T>
    std::string operator()(T const&, T const&) const { return "identical"; }

    std::string operator()(A const&, B const&) const { return "A, B"; }
    std::string operator()(A const&, C const&) const { return "A, C"; }

    std::string operator()(Base const&, A const&) const { return "[ABC], A"; }

    template <typename... Other>
        std::string operator()(Other const&...) const { return "Other"; }
};

int main()
{
    MyBehaviour f;

    MyType a = A{},
           b = B{},
           c = C{};

    std::cout << boost::apply_visitor(f, a, b) << "\n";
    std::cout << boost::apply_visitor(f, a, c) << "\n";
    
    std::cout << boost::apply_visitor(f, a, a) << "\n";
    std::cout << boost::apply_visitor(f, b, b) << "\n";
    std::cout << boost::apply_visitor(f, c, c) << "\n";
    
    std::cout << boost::apply_visitor(f, c, a) << "\n";

    std::cout << boost::apply_visitor(f, c, b) << "\n";
}
        
