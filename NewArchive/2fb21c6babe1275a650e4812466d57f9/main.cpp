#include <exception>
#include <iostream>
#include <type_traits>

extern "C" {
    template<class R, class... Args>
    using F = R(*)(Args...);
}

template<class R, class... Args, class G>
typename std::result_of<F<R, Args...>>::type call_c(F<R, Args...> f, G g) {
    using S = typename std::result_of<G>::type;

    try {
        throw g;
    } catch (G const& g) {
        return f([] (Brgs&&... args) -> S {
            try {
                auto ptr = std::current_exception();
                std::rethrow_exception(ptr);
            } catch (G const& h) {
                return h(std::forward<Brgs>(args)...);
            }
        });
    }
}

extern "C" void foo(F<void, int> some_callback) {
    some_callback(42);
}

int main() {
    int i = 0;
    call_c(foo, [&] (int x) {
        i = x;
    });
    std::cout << i << '\n';
}
