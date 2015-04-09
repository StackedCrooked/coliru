#include <boost/range/adaptors.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::adaptors;

class warrior {
    bool alive;
    std::string name;
public:
    warrior(std::string name) : name{std::move(name)}
    { }

    std::string getName() const { return name; }

    bool isAlive() const {
        static bool val = true;
        return val = !val;
    }
};

class vm{
    std::vector<warrior> _warriors;
public:
    vm(std::vector<warrior> w) : _warriors{std::move(w)}
    { }

    auto getAlive() const {
        return _warriors | filtered(std::mem_fn(&warrior::isAlive));
    }
};

int main() {
    vm myvm{std::vector<warrior>{warrior("one"), warrior("two"), warrior("three"), warrior("four")}};
    for (auto&& w : myvm.getAlive()) {
        std::cout << w.getName() << "\n";
    }
}