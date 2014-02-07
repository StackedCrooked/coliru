#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T, size_t Size>
struct static_array {
    static const size_t size = Size;
    T array[Size];
    static_array() {}
    static_array(T init) {
        std::fill(std::begin(array), std::end(array), init);
    }
    T & operator[](size_t index) {
        if (index >= size) {
            throw std::range_error("index out of bound");
        }
        return array[index];
    }
};

static void printif(bool test) {
    if (test) {
        std::cout << "hello world\n";
    }
}

int main() {
    int cout{9};
    std::cout << (cout << cout << '\n');
    printif(true);
    std::cout << sizeof(static_array<int, 15>) << '\n';

    static_array<int, 15> vec(6);
    static_array<int, 15> vec2 = vec;
    
    vec = vec2;
    std::cout << vec.size << '\n';
    std::cout << vec.array[0] << " " << vec.array[1] << '\n';
    std::cout << vec2.array[0] << " " << vec2.array[1] << '\n';
}