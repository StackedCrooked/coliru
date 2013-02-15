#include <functional>
#include <iostream>
#include <string>
#include <boost/optional.hpp>

template<class T>
class Maybe {
private:
    boost::optional<T> value;

public:
    using value_type = T;

    Maybe() = default;
    explicit Maybe(T t) : value{std::move(t)} {}

    bool isJust() const { return static_cast<bool>(value); }
    bool isNothing() const { return !value; }

    T const& operator*() const {
        return *value;
    }

    template<class F, class U = typename std::result_of<F(T const&)>::type::value_type>
    Maybe<U> operator>>=(F f) {
        if (isNothing()) return Maybe<U>{};
        return f(*value);
    }
};

template<class T>
std::string show(Maybe<T> const& m) {
    if (m.isJust()) return "Just " + std::to_string(*m);
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
