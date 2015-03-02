#include <iostream>

template <bool C, template <int> class T, template <int> class F>
struct conditional_template {
    template <int I>
    using type = T<I>;
};

template <template <int> class T, template <int> class F>
struct conditional_template<false, T, F> {
    template <int I>
    using type = F<I>;
};

template <int I>
struct invoke;

template <int I>
struct nothing { 
    static void
    call() { }
};

template <int I>
void f() {
    std::cout << I << '\n';
    conditional_template<(I > 0), invoke, nothing>::template type<I - 1>::call();
}

template <int I>
struct invoke {
    static void
    call() {
        f<I>();
    }
};

int
main() {
    f<5>();
}
