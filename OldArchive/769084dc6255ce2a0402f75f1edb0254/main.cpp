#include <utility>
#include <iostream>

template <template <class> class H, typename F>
struct N {
    N() = delete;

    static F f() {
        H<F> h;
        return h();
    }
};

template <class T>
struct H {
    H() = default;

    T operator()() {
        return T();
    }
};

template <template <class> class T>
int h() {
    return N<T, decltype( std::declval<T<int>>().operator()() )>::f();
}

int main() {

    std::cout << h<H>();

}