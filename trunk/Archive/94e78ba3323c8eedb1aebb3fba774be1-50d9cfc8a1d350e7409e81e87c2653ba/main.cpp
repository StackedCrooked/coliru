#include <vector>
#include <iostream>

template<typename range, typename comp>
void foo(range rng, comp c) {
    std::cout << "range" << std::endl;
}

template<typename iter>
void foo(iter a, iter b) {
    std::cout << "iter" << std::endl;
}


int main() {
    std::vector<int> v{1, 2, 3};
    foo(v.begin(), v.end());
    foo(v, [] {});
}