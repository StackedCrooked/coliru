#include <iostream>
#include <memory>
#include <boost/variant.hpp>

using Human = int;          // just an 
using Zombie = double;      // example

using Humanoid = boost::variant<Human, Zombie>;

const std::string name(const Humanoid& x) {
    if (x.type() == typeid(Human))
        return "Human";
    if (x.type() == typeid(Zombie))
        return "Zombie";
    return "Don't know";
}

int main() {
    Zombie x = 5;
    std::cout << name(x);
    return 0;
}