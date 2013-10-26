#include <iostream>
#include <memory>
#include <boost/variant.hpp>

using Human = int;          // just an 
using Zombie = double;      // example

using Humanoid = boost::variant<Human, Zombie>;

std::string name(Human const&)  { return "Human"; }
std::string name(Zombie const&) { return "Zombie"; }

struct name_visitor : boost::static_visitor<std::string> {
    template<typename... T>
    std::string operator()(T&&... args) const { return name(std::forward<T>(args)...); }
};

template <typename... T>
std::string name(boost::variant<T...> const& x) {
    return boost::apply_visitor(name_visitor(), x);
}

int main() {
    Zombie x = 5;
    std::cout << name(x);
    return 0;
}
