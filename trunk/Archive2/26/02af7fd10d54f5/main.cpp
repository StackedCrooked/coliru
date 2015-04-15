#include <iostream>

template <unsigned, typename...>
struct choose_fun;

template <unsigned I, typename F, typename... Rest>
struct choose_fun<I, F, Rest...> {
    static int
    go(unsigned n, int a, int b, F const& f, Rest const&... rest) {
        if (n == I)
            return f(a, b);
        
        return choose_fun<I + 1, Rest...>::go(n, a, b, rest...);
    }
};

template <unsigned I>
struct choose_fun<I> {
    static int
    go(unsigned, int, int) {
        throw "Nooooes!";
    }
};

template <typename... Fs>
int
choose(unsigned n, int a, int b, Fs const&... fs) {
    return choose_fun<0, Fs...>::go(n, a, b, fs...);
}

template <typename... Fs>
auto
f(Fs const&... fs) {
    return [fs...] (unsigned n, int a, int b) { 
        return choose(n, a, b, fs...);
    };
}

int
main() {
    auto g = f(
        [] (int a, int b) { return a + b; },
        [] (int a, int b) { return a - b; },
        [] (int a, int b) { return a * b; }
    );
    
    std::cout << g(0, 2, 3) << '\n'
              << g(1, 5, 1) << '\n'
              << g(2, 9, 7) << '\n';
}
