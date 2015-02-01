#include <utility>
#include <type_traits>

// LINQ is lazy so.. expression template time

// this encapsulates the basic building block. A pipeable function.
template<typename Functor>
struct pipeable : public Functor {
    template<typename... Args>
    pipeable(Args&&... args): Functor(std::forward<Args>(args)...) {}

    // operator() is inherited
};

// represents an actual expression, expression<f, g> -> g(f())
// note that this is executed left to right not right to left
template<typename First, typename Second>
struct expression {
private:
    First lhs;
    Second rhs;
public:
    expression(First lhs, Second rhs): lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    template<typename... Args>
    auto operator()(Args&&... args) const -> decltype(rhs(lhs(std::forward<Args>(args)...))) {
        return rhs(lhs(std::forward<Args>(args)...));
    }
};

template<typename T>
struct is_pipeable : std::false_type {};

template<typename T>
struct is_pipeable<pipeable<T>> : std::true_type {};

template<typename T, typename U>
struct is_pipeable<expression<T, U>> : std::true_type {};

// x | f | g | h
// (((x | f) | g) | h)
// expression<expression<expression<x, f>, g>, h>

template<typename First, typename Second, typename Result = expression<First, Second>,
         typename std::enable_if<is_pipeable<First>::value and is_pipeable<Second>::value, int>::type = 0>
inline Result operator|(const First& lhs, const Second& rhs) {
    return Result{lhs, rhs};
}

#include <iostream>
#include <algorithm>

template<typename Container>
struct from_type {
private:
    Container c;
public:
    from_type(Container c): c(std::move(c)) {}

    Container operator()() const {
        return c;
    }
};

template<typename Predicate>
struct filter_type {
private:
    Predicate p;
public:
    filter_type(Predicate p): p(std::move(p)) {}

    template<typename Container>
    Container operator()(Container c) const {
        // for vectors only atm, you know a demo.
        using std::begin;
        using std::end;
        auto first = begin(c);
        auto last  = end(c);
        c.erase(std::remove_if(first, last, [this](decltype(*first) x) { return !p(x); }), last);
        return c;
    }
};

template<typename Container>
inline pipeable<from_type<Container>> from(Container c) {
    return { std::move(c) };
}

template<typename Predicate>
inline pipeable<filter_type<Predicate>> filter(Predicate p) {
    return { std::move(p) };
}

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto test = from(v) | filter([](int x) { return x % 2 != 0; });
    auto&& result = test();

    for(auto&& x : result) {
        std::cout << x << '\n';
    }
}
