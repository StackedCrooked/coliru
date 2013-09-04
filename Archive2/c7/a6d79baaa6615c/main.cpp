#include <cstddef>

template<std::size_t> class C {};

int main() {
    C<4> c;
    C<4> * const p = &c;
}