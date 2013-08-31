#include <vector>
#include <iostream>

struct any{ template<class... T> any(T&&...){} };

template<typename range>
void foo(range rng, any c) {
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