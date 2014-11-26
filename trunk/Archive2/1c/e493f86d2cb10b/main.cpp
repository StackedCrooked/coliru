#include <iostream>
#include <functional>
#include <utility>

template<class T>
auto make_monad(T&& arg) {
    return [captive = std::forward<T>(arg)](auto&& a) {
        std::cout << __PRETTY_FUNCTION__ << ' ' << captive << ": " << a << '\n';
        return 1;
    };
}

template<class T>
auto make_monad(std::reference_wrapper<T> arg) {
    return [&captive = arg.get()](auto&& a) {
        std::cout << __PRETTY_FUNCTION__ << ' ' << captive << ": " << a << '\n';
        return 1;
    };
}

int main() {
    auto monad = [](auto&& captive) {
        return make_monad(std::forward<decltype(captive)>(captive));
    };

    int n = 1;
    monad(1)(1);
    monad(n)(2);
    monad(std::ref(n))(3);
}
