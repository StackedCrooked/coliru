#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
int main() {
    std::string to_port("8004");
    std::cout << boost::lexical_cast<unsigned short>(to_port) << "\n";
}
