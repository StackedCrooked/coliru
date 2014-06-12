#include <iostream>
#include <vector>

template<typename Container>
void enumerate(const Container& t) {
    std::size_t i = 0;
    for(auto it = t.begin(); it != t.end(); ++it, ++i)
        std::cout << i << *it << std::endl;
}

int main() {
    enumerate(std::vector<int>{2,3,9});
}