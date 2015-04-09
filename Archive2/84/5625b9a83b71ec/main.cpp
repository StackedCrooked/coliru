#include <boost/range/adaptors.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::adaptors;

class pooper {
public:
    bool poop() const {
        static auto result = false;
        return result = !result;
    }
};

std::string to_string(pooper const&) const {
    return "💩\n";
}

int main() {
    std::vector<pooper> poopers{pooper(), pooper(), pooper(), pooper(), pooper()};
    for (auto&& pooper : poopers | filtered(std::mem_fn(&pooper::poop))) {
        std::cout << to_string(pooper);
    }
}