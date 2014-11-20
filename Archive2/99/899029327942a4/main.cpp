#include <boost/format.hpp>
#include <boost/format/group.hpp>
#include <iostream>
#include <iomanip>

using namespace boost;

int main(int argc, char const**) {
    std::cout << format("%u") % io::group(std::setw(argc-1), std::setfill('0'), 42);
}
