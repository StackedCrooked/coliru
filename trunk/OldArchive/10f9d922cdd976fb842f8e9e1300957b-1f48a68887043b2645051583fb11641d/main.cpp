#include <boost/optional.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

template<typename T>
using result = boost::optional<std::pair<T, std::string>>;

template<typename T>
using parser = std::function<result<T>(std::string const&)>;

template<typename T>
parser<T> inject(T x) {
    return [=] (std::string const& xs) { return result<T>{std::make_pair(x, xs)}; };
}

template<typename T, typename U>
parser<U> operator>=(parser<T> p, std::function<parser<U>(T)> k) {
    return [=] (std::string const& cs) {
        auto r = p(cs);
        if (!r) return boost::none;
        return k(r.first)(r.second);
    };
}

template<typename T, typename U>
parser<U> operator>>(parser<T> p, parser<U> q) {
    return p >= [=] (T) { return q; };
}

parser<char> const item = [] (std::string const& xs) {
    return xs == "" ? boost::none : result<char>{std::make_pair(xs.front(), xs.substr(1))};
};

int main() {
    auto p = item >> item >> item;
    std::cout << (bool)p("abc") << '\n';
}
