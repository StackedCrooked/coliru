#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

unsigned rotatenumber(unsigned n, unsigned rotate_right_by) {
    std::string str = std::to_string(n);
    assert(rotate_right_by<=str.size());
    std::rotate(str.begin(), str.begin()+rotate_right_by, str.end());
    std::istringstream ss(str);
    ss >> n;
    return n;
}

int main() {
    std::cout << rotatenumber(25314,3) << '\n';
    std::cout << rotatenumber(32546,4) << '\n';
}