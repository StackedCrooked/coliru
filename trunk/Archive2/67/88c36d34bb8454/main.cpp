#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<boost::variant<std::string, float>> values;
    values.emplace_back("a");
    values.emplace_back("b");
    values.emplace_back(3.14);
    values.emplace_back("d");
    values.emplace_back(2.72);

    struct : boost::static_visitor<> {
        void operator()(std::string const& x) const {
            std::cout << "got string: " << x << '\n';
        }

        void operator()(float x) const {
            std::cout << "got float: " << x << '\n';
        }
    } visitor;
    for (auto&& value : values) {
        boost::apply_visitor(visitor, value);
    }
}
