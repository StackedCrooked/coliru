#include <algorithm>
#include <string>
#include <iostream>

int main() {
    std::string str = "0123456789";
    for(size_t i = 1; i < 1000000; ++i) {
        std::next_permutation(str.begin(),str.end());
    }
    std::cout << str;
}