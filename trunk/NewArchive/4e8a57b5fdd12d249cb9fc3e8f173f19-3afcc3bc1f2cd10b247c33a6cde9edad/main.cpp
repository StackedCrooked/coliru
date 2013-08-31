#include <vector>
#include <iostream>


int main() {
    std::vector<int> v = { 1, 5, 23, 2, 44 };
    auto iter = v.begin();
    for (std::size_t i = 0; i != v.size() + 1; ++i, ++iter) {
        if(iter == v.end()) {
            std::cout << "END!" << std::endl;
        }
        else {
            std::cout << *iter << std::endl;
        }
    }
}