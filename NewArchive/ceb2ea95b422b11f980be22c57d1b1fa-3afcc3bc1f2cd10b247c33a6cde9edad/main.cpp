#include <vector>
#include <iostream>


template<typename IterType>
void print(IterType iter /* begin */, IterType end) {
    auto size = std::distance(iter, end);
    for (decltype(size) i = 0; i != size + 1; ++i, ++iter) {
        if(iter == end) {
            std::cout << "END!" << std::endl;
        }
        else {
            std::cout << *iter << std::endl;
        }
    }
}


int main() {
    std::vector<int> v = { 1, 5, 23, 2, 44 };
    print(v.begin(), v.end());
}