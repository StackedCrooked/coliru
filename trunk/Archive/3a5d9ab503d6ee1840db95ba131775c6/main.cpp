#include <iostream>
#include <initializer_list>

template<typename T,size_t N>
struct Sample {
    T array[N];
    Sample(std::initializer_list<T> l) {
        std::copy(l.begin(),l.end(),std::begin(array));
    }
    T operator[](size_t index) {
        return array[index];
    }
};

int main() {
    Sample<int,5> S({1,2,3,4,5});
    std::cout << S[2];
}