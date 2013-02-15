#include <boost/variant.hpp>
#include <vector>
#include <string>
int main() {
    typedef boost::make_recursive_variant<int, short, char, long, std::vector<std::string>, boost::recursive_variant_>::type loltype;
    loltype first, second;
    second = first;
}