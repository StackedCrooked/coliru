#include <iostream>
#include <stdexcept>
#include <tuple>

class bad_match : public std::runtime_error {
public:
    bad_match(char const* msg) : std::runtime_error(msg) {}
    bad_match(std::string const& msg) : std::runtime_error(msg) {}
};

template<size_t... n>
struct ct_integers_list {
    template <size_t m>
    struct push_back {
        typedef ct_integers_list<n..., m> type;
    };
};

template<std::size_t max>
struct ct_iota_1 {
    typedef typename ct_iota_1<max-1>::type::template push_back<max>::type type;
};

template<>
struct ct_iota_1<0> {
    typedef ct_integers_list<> type;
};

template<std::size_t... indices, typename Tuple>
auto tuple_subset(const Tuple& tpl, ct_integers_list<indices...>)
    -> decltype(std::make_tuple(std::get<indices>(tpl)...)) {
    return std::make_tuple(std::get<indices>(tpl)...);
}

template <typename Head, typename... Tail>
std::tuple<Tail...> tuple_tail(const std::tuple<Head, Tail...>& tpl) {
    return tuple_subset(tpl, typename ct_iota_1<sizeof...(Tail)>::type());
}

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
    matcher(Us&... argz) : args{argz...} {}

    template<class U, class... Us>
    matcher<Ts...>& operator=(std::tuple<U, Us...> tup) {
        match(args, tup);
        args = tup;
        return *this;
    }

private:
    static void match(std::tuple<> const&, std::tuple<> const&) {}

    template<class... Us, class V, class... Vs, class W, class X>
    static void match(std::tuple<predicate<W, X>, Us...> const& a, std::tuple<V, Vs...> const& b) {
        if (!std::get<0>(a).match(std::get<0>(b))) throw bad_match{"bad_match"};
        match(tuple_tail(a), tuple_tail(b));
    }

    template<class U, class... Us, class V, class... Vs>
    static void match(std::tuple<U, Us...> const& a, std::tuple<V, Vs...> const& b) {
        match(tuple_tail(a), tuple_tail(b));
    }

    std::tuple<Ts&...> args;
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
