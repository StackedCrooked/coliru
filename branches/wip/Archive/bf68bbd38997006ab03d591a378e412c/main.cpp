#include <iostream>
#include <stdexcept>
#include <tuple>
#include <type_traits>

class bad_match : public std::runtime_error {
public:
    bad_match(char const* msg) : std::runtime_error(msg) {}
    bad_match(std::string const& msg) : std::runtime_error(msg) {}
};

template<class T, class F>
class predicate {
public:
    explicit predicate(T const& t, F const& f = F())
    : value(t)
    , pred(f) {}

    bool match(T const& value2) {
        return pred(value, value2);
    }

    template<class U>
    predicate<T ,F>& operator=(U const&) {
        return *this;
    }

private:
    T value;
    F pred;
};

template<class T>
struct is_predicate : std::integral_constant<bool, false> { };

template<class T, class F>
struct is_predicate<predicate<T, F>> : std::integral_constant<bool, true> { };

template<class T>
struct op_eq {
    bool operator()(T const& a, T const& b) {
        return a == b;
    }
};

template<class T>
struct op_gt {
    bool operator()(T const& a, T const& b) {
        return a > b;
    }
};

template<class T> using eq_pred = predicate<T, op_eq<T>>;
template<class T> using gt_pred = predicate<T, op_gt<T>>;

template<class... Ts>
class matcher {
public:
    template<class... Us>
    matcher(Us&&... argz) : args{argz...} { }

    template<class U, class... Us>
    matcher<Ts...>& operator=(std::tuple<U, Us...> tup) {
        match<0>(tup);
        args = tup;
        return *this;
    }

private:
    std::tuple<Ts&...> args;

    template<std::size_t I, class... Us>
    typename std::enable_if<I == sizeof...(Us) - 1>::type
    match(std::tuple<Us...> const&) { }

    template<std::size_t I, class... Us>
    typename std::enable_if<I < sizeof...(Us) - 1 && is_predicate<decltype(std::get<I>(args))>::value>::type
    match(std::tuple<Us...> const& tup) {
        if (std::get<I>(args).match(std::get<I>(tup))) {
            throw bad_match{"bad_match"};
        }
        match<I + 1>(tup);
    }

    template<std::size_t I, class... Us>
    typename std::enable_if<I < sizeof...(Us) - 1 && !is_predicate<decltype(std::get<I>(args))>::value>::type
    match(std::tuple<Us...> const& tup) {
        match<I + 1>(tup);
    }
};

template<class... Ts>
matcher<Ts...> match_tie(Ts&&... ts) {
    return matcher<Ts...>{ts...};
}

int main() {
    int a, b, c;
    match_tie(a, b, eq_pred<int>{42}, c) = std::make_tuple(1, 2, 42, 3);
    std::cout << a << ", " << b << ", " << c << '\n';

    try {
        match_tie(a, b, eq_pred<int>{43}, c) = std::make_tuple(1, 2, 42, 3);
        std::cout << a << ", " << b << ", " << c << '\n';
    } catch (bad_match const& e) {
        std::cerr << e.what() << '\n';
    }
}
