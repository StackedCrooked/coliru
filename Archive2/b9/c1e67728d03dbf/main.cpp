#include <algorithm>
#include <boost/optional.hpp>
#include <cassert>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <vector>

using runtime_signature = std::vector<std::type_index>;
using overload_set      = std::set<runtime_signature>;

template<class Set, class... Args>
boost::optional<runtime_signature> resolve_overloads(Set const& overloads, Args...) {
    auto match = overloads.find(runtime_signature { typeid(Args)... });
    if (overloads.end() == match)
        return boost::none;
    return *match;
}

int main() {
    overload_set const candidates {
        { typeid(int), typeid(double) },
        { typeid(std::string), typeid(float) },
    };

    std::cout << "Getting first overload: \n";
    auto matched1 = resolve_overloads(candidates, 1, 2.0);
    assert(matched1);
    
    std::cout << "Getting second overload: \n";
    using std::operator ""s;
    auto matched2 = resolve_overloads(candidates, "hello world"s, 69.0f);
    assert(matched2);
    assert(matched1 != matched2);

    std::cout << "Getting empty set: \n";
    auto matched3 = resolve_overloads(candidates, "hello world"s, 69.0f, "willy wonka is a nasty man");
    assert(!matched3);

    std::cout << "All done\n";
}