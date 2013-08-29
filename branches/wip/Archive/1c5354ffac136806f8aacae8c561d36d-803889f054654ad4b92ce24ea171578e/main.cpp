#include <type_traits>
#include <stdexcept>


template<class T, int count>
struct array {
    array() : data() {}
    
    template<int N>
    T& operator[](std::integral_constant<int,N> index) {
        if (N>=count)
            throw std::out_of_range("out of range");
        return data[N];
    }
private:
    T data[count];
};

#include <iostream>
int main() {
    array<float, 3> thingy;

    std::integral_constant<int, 2> index2;
    std::cout << thingy[index2] << '\n';

    std::integral_constant<int, 3> index3;
    std::cout << thingy[index3] << '\n';
}