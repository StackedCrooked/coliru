#include <functional>
#include <iostream>

template <typename T> T& get_reference_object(T&& t) { return t; }

template <typename T> T& get_reference_object(std::reference_wrapper<T> t) { return t.get(); }

struct S
{
    int n;
};

int main()
{
    auto monad = [](auto && captive) {
        return [captive = captive](auto&& a) { return get_reference_object(captive).n + a; };
    };

    S s{1};
    std::cout << monad(s)(2) << std::endl;
    std::cout << monad(std::ref(s))(3) << std::endl;
}
