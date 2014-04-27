#include <cstdlib>
#include <iostream>

std::size_t constexpr index[] {
    2, 5, 3, 1, 6, 4, 8, 0, 9, 7
};

template <std::size_t M, std::size_t I = 0>
struct loop_thingy {
    static int
    do_(int* array, int accum = 0) {
        return loop_thingy<M, I + 1>::do_(array, accum + array[index[I]]);
    }
};

template <std::size_t M>
struct loop_thingy<M, M> {
    static int
    do_(int*, int accum) {
        return accum;
    }
};

int
main() {
    int data[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << loop_thingy<10>::do_(data) << '\n';
}
