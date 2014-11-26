#include <functional>
#include <iostream>

template <typename T> T& get_reference_object(T&& t) { return t; }

template <typename T> T& get_reference_object(std::reference_wrapper<T> t) { return t.get(); }

int main()
{
    auto monad = [](auto && captive) {
        return [&captive = get_reference_object(captive)](auto&& a) { return ++captive; };
    };

    int n = 1;
    monad(1)(1);
    monad(n)(2);
    std::cout << n << std::endl;
    monad(std::ref(n))(3);
    std::cout << n << std::endl;
}
