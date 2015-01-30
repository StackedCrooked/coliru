template <unsigned N> struct faux_unroll {
    template <typename F> static void call(F const& f) {
        f();
        faux_unroll<N-1>::call(f);
    }
};

template <> struct faux_unroll<0u> {
    template <typename F> static void call(F const&) {}
};

#include <iostream>
#include <cstdlib>

int main() {
    srand(time(0));

    double r = 0;
    faux_unroll<10>::call([&] { r += 1.0/rand(); });

    std::cout << r;
}
