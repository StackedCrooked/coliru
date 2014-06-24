#include <boost/tuple/tuple.hpp>
#include <iostream>

int main() {
    boost::tuple<std::string, double> t = boost::make_tuple("John Doe", 4.815162342);
    std::cout << boost::get<0>(t) << '\n';
    std::cout << boost::get<1>(t) << '\n';
}