#include <boost/any.hpp>
#include <string>
#include <iostream>

int main() {
    boost::any x;
    x = std::string("Si");
    std::cout << boost::any_cast<std::string>(x);
}