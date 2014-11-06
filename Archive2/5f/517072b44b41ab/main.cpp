#include <boost/variant.hpp>

#include <iostream>

struct A { std::string a_property; };
struct B { std::string b_field;    };

using namespace boost;

struct select_member : static_visitor<std::string&> {
    std::string& operator()(A& a) const { return a.a_property; }
    std::string& operator()(B& b) const { return b.b_field;    }
};

int main()
{
    variant<A,B> v = A { "some string" };

    apply_visitor(select_member(), v) += " suffix";

    std::cout << get<A>(v).a_property << "\n"; // prints "some string suffix"
}
