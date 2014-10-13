#include <iostream>
#include <utility>

template <typename T>
struct Wrapper {
    T t;
};

template <typename T>
struct Proxy {
    T t;
    void operator()() const { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

template <typename T>
struct remove_rvalue_reference {
    using type = T;
};

template <typename T>
struct remove_rvalue_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;

template <typename Wrapper>
auto createProxy(Wrapper&& w) ->
  Proxy<remove_rvalue_reference_t<decltype((std::forward<Wrapper>(w).t))>> {
    return {std::forward<Wrapper>(w).t};
}

int main() {
    Wrapper<int> w{13};
    createProxy(w)();
    createProxy(const_cast<decltype(w) const&>(w))();
    createProxy(Wrapper<int>{42})();
}
