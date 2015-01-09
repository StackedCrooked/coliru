#include <boost/variant.hpp>
#include <map>
#include <vector>
#include <string>


using Val = boost::variant<std::vector<int>, std::vector<std::string>>;
using Ref = boost::variant<std::vector<int>&, std::vector<std::string>& >;

std::map<std::string, Val> map {
    { "first", std::vector<int> { 1,2,3,4 } },
    { "2nd",   std::vector<std::string> { "five", "six", "seven", "eight" } }
};

namespace { // detail
    template <typename T>
    struct implicit_convert : boost::static_visitor<T> {
        template <typename U> T operator()(U&& u) const { return std::forward<U>(u); }
    };
}

Ref getVal(std::string& name) {
    return boost::apply_visitor(implicit_convert<Ref>(), map[name]);
}

#include <iostream>

int main() {
    for (auto i : boost::get<std::vector<int>         >(map["first"])) std::cout << i << " ";
    for (auto i : boost::get<std::vector<std::string> >(map["2nd"]))   std::cout << i << " ";
}
