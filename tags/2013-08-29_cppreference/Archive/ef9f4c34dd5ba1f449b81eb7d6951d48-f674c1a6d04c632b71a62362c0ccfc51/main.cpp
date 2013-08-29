#include <iostream>
#include <type_traits>


template<typename T, unsigned int power, unsigned int bits>
struct flp2_impl {
    static T calc(T x)
    {
        x = x | (x >> power);
        return flp2_impl<T, power * 2, bits / 2>::calc(x);
    }
};


template<typename T, unsigned int power>
struct flp2_impl<T, power, 1> {
    static T calc(T x) {
        return x | (x >> power);
    }
};


template<typename T>
T flp2(T x) {
    x = flp2_impl<T, 1, sizeof(T) * 8>::calc(x);
    return x - (x >> 1);
}


int main() {
    std::cout << flp2(20);
}