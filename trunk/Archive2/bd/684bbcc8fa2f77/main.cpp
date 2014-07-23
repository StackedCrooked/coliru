#include <iostream>

struct m {
    int i;
};

template <typename T>
struct remove_member_pointer;

template <typename R, typename T>
struct remove_member_pointer<R T::*> {
    typedef R type;
};

int main() {
    typedef decltype(&m::i) mi_t;
    typedef typename remove_member_pointer<mi_t>::type i_t;
    struct {} _ = i_t{};
}