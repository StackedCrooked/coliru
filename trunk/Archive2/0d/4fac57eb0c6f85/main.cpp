#include <vector>
#include <iostream>
#include "boost/unordered_map.hpp"

int main() {
    std::vector<unsigned char> v;
    v.push_back('a');
    std::cout << "Hello " << v[0] << std::endl;
}
