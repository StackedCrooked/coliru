#include <boost/lexical_cast.hpp>
#include <iostream>

int main() {
    int x = boost::lexical_cast<int>("3");
    std::cout << x << '\n';
}