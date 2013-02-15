#include <functional>
#include <iostream>
#include <string>
#include <boost/optional.hpp>

template<class I>
using Maybe = boost::optional<I>;

template<class I, class F, class R = typename std::result_of<F(const I&)>::type::value_type>
Maybe<R> operator>>=(Maybe<I> m, F f) {
    if (m) return f(m.get());
    return Maybe<R>{};
}




template<class T>
std::string show(Maybe<T> const& m) {
    if (m) return "Just " + std::to_string(*m);
    return "Nothing";
}

int main() {
    auto nothing1 = Maybe<int>{42} >>= [] (int) { return Maybe<double>(); };
    auto nothing2 = nothing1 >>= [] (int x) { return Maybe<int>(x * 2); };
    auto something = Maybe<double>{3.14} >>= [] (double x) { return Maybe<double>(x / 2) >>= [] (double y) { return Maybe<double>{y * 42}; }; };
    std::cout << show(nothing1) << '\n';
    std::cout << show(nothing2) << '\n';
    std::cout << show(something) << '\n';
}
