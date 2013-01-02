#include <stdexcept>
#include <exception>
#include <iostream>
#include <algorithm>
#include <initializer_list>

template<typename T, size_t N>
struct Garbage {
    static_assert(!(N < 4), "Length way too small bro");
    T array[N];
    Garbage(std::initializer_list<T> l) {
        std::copy(l.begin(),l.end(),std::begin(array));
    }
};

int main() {
    Garbage<int,3> v = {1,2,3};
}