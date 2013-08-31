// Making an array with variadic templates

#include <iostream>

template<typename T, typename... Args>
void make_array(Args&&... args) {
    T array[sizeof...(args)] = { args... };
    for(auto&& i : array) {
        std::cout << i << ' ';
    }
}

int main() {
    make_array<int>(1,2,3,4,5,6,7);
}