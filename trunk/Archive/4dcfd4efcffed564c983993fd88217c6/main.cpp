#include <iostream>
#include <array>
#include <initializer_list>

template<typename T, size_t N>
class Wrapper {
public:
    std::array<T,N> arrays;
    Wrapper(std::initializer_list<T> l) {
        std::copy(l.begin(),l.end(),std::begin(arrays));
    }
    T operator[](size_t n) {
        return arrays[n];
    }
};

int main() {
    Wrapper<int,5> v = {1,2,3,4,5};
    std::cout << v[4];
}