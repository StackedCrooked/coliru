#include <iostream>
#include <sstream>
#include <iterator>

int main() {
    std::istringstream some_string ( "-0.003  79350   -0.267  147");
    std::cout << std::distance(std::istream_iterator<double>(some_string), {});
}
