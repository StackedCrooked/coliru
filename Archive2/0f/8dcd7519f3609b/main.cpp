#include <initializer_list>

template<int i> class A {};

template<class T>
constexpr auto f(const std::initializer_list<T>& x) { return A<x.size()>(); }


int main(int argc, char **argv) {
    f({1, 3});

    return 0;
}
