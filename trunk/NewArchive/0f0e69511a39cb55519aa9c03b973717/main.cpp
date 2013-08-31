#include <iostream>
#include <stdexcept>
#include <tuple>

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
    matcher<Ts...>& operator=(std::tuple<U, Us...> t) {
        do_match<0>(t);
        do_assign<0>(t);
        return *this;
    }

private:
    void do_match(std::tuple<> const&) {}

    template<std::size_t I, class V, class W, class... Us>
    void do_match(std::tuple<predicate<V, W>, Us...> const& tup) {
        if (!std::get<0>(tup).match(std::get<I>(args))) {
            throw std::runtime_error{"match error"};
        }

        do_match<I + 1>(tuple_tail(tup));
    }

    template<std::size_t I, class U, class... Us>
    void do_match(std::tuple<U, Us...> const& tup) {
        do_match<I + 1>(tuple_tail(tup));
    }

    void do_assign(std::tuple<> const&) {}

    template<std::size_t I, class V, class W, class... Us>
    void do_assign(std::tuple<predicate<V, W>, Us...> const& tup) {
        do_assign<I + 1>(tuple_tail(tup));
    }

    template<std::size_t I, class U, class... Us>
    void do_assign(std::tuple<U, Us...> tup) {
        std::get<I>(args) = std::get<0>(tup);
        do_assign<I + 1>(tuple_tail(tup));
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
    } catch (std::exception const& e) {
        std::cerr << e.what() << '\n';
    }
}
