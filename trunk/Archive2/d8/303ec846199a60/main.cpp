#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    std::ostream_iterator<T> out(os, " ");
    std::copy(std::begin(vec), std::end(vec), out);
    return os;
}


int main() {
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}