#include <iostream>

enum MujEnum { X, Y };

template <typename F, size_t N, MujEnum e>
struct f_impl {
    static void
    do_() {
        std::cout << "Prvni\n";
    }
};

template <size_t N>
struct f_impl<float, N, X> {
    static void
    do_() {
        std::cout << "Druha\n";
    }
};

template <typename F, size_t N, MujEnum e> 
void
f() {
    f_impl<F, N, e>::do_();
}

int
main() {
    f<int, 4, X>();
    f<float, 9, Y>();
    f<float, 2, X>();
}
