#include <iostream>
#include <memory>
#include <boost/variant.hpp>

using Human = int;          // just an 
using Zombie = double;      // example

using Humanoid = boost::variant<Human, Zombie>;

const std::string name(Human const&)  { return "Human"; }
const std::string name(Zombie const&) { return "Zombie"; }

struct name_visitor : boost::static_visitor<std::string> {
    template<typename... T>
    std::string operator()(T&&... args) const { return name(std::forward<T>(args)...); }
};

template <typename... T>
const std::string name(boost::variant<T...> const& x) {
    const static name_visitor visitor;
    return boost::apply_visitor(visitor, x);
}

int main() {
    Zombie x = 5;
    std::cout << name(x);
    return 0;
}
