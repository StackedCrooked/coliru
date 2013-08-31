#include <gears/meta.hpp>

using namespace gears;

template<typename T, typename U, typename V>
struct triple {
    using first_type  = T;
    using second_type = U;
    using third_type  = V;

    T first;
    U second;
    V third;

    constexpr triple()              = default;
    constexpr triple(const triple&) = default;
    constexpr triple(triple&&)      = default;

    constexpr triple(T&& a, U&& b, V&& c) noexcept: first(std::forward<T>(a)), second(std::forward<U>(b)), third(std::forward<V>(c)) {}

    template<class X, class Y, class Z, EnableIf<std::is_convertible<X, T>, std::is_convertible<Y, U>, std::is_convertible<Z, V>>...>
    constexpr triple(const triple<X, Y, Z>& t) noexcept: first(t.first), second(t.second), third(t.third) {}

    template<class X, class Y, class Z, EnableIf<std::is_convertible<X, T>, std::is_convertible<Y, U>, std::is_convertible<Z, V>>...>
    constexpr triple(triple<X, Y, Z>&& t) noexcept: first(std::forward<X>(t.first)), second(std::forward<Y>(t.second)), third(std::forward<Z>(t.third)) {}

    void swap(triple& t) noexcept(noexcept(std::swap(first, t.first))   &&
                                  noexcept(std::swap(second, t.second)) &&
                                  noexcept(std::swap(third, t.third))) {
        using std::swap;
        swap(first, t.first);
        swap(second, t.second);
        swap(third, t.third);
    }
};

template<typename T, typename U, typename V>
constexpr bool operator==(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second && lhs.third == rhs.third;
}

template<typename T, typename U, typename V>
constexpr bool operator<(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return   lhs.first < rhs.first  ? true  :
             rhs.first < lhs.first  ? false :
            lhs.second < rhs.second ? true  :
            rhs.second < lhs.second ? false :
             lhs.third < rhs.third;
}

template<typename T, typename U, typename V>
constexpr bool operator!=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs == rhs);
}

template<typename T, typename U, typename V>
constexpr bool operator>(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return (rhs < lhs);
}

template<typename T, typename U, typename V>
constexpr bool operator>=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs < rhs);
}

template<typename T, typename U, typename V>
constexpr bool operator<=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(rhs < lhs);
}

template<typename T, typename U, typename V>
inline void swap(triple<T, U, V>& lhs, triple<T, U, V>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

namespace std {
template<typename T> struct tuple_size;
template<size_t N, typename T> struct tuple_element;

template<typename T, typename U, typename V>
struct tuple_size<triple<T, U, V>> {
    static constexpr size_t value = 3;
};

template<typename T, typename U, typename V>
struct tuple_element<0, triple<T, U, V>> {
    using type = T;
};

template<typename T, typename U, typename V>
struct tuple_element<1, triple<T, U, V>> {
    using type = U;
};

template<typename T, typename U, typename V>
struct tuple_element<2, triple<T, U, V>> {
    using type = V;
};

template<size_t N, typename T, typename U, typename V>
constexpr Type<tuple_element<N, triple<T, U, V>>>& get(triple<T, U, V>& t) noexcept {
    static_assert(N < 3, "Can only use get on a triple with less than 3");
    return N == 0 ? t.first  :
           N == 1 ? t.second :
           t.third;
}

template<size_t N, typename T, typename U, typename V>
constexpr Type<tuple_element<N, triple<T,U,V>>>& get(const triple<T, U, V>& t) noexcept {
    static_assert(N < 3, "Can only use get on a triple with less than 3");
    return N == 0 ? t.first  :
           N == 1 ? t.second :
           t.third;
}

template<size_t N, typename T, typename U, typename V>
constexpr Type<tuple_element<N, triple<T, U, V>>>&& get(triple<T, U, V>&& t) noexcept {
    static_assert(N < 3, "Can only use get on a triple with less than 3");
    using triple_type = Type<tuple_element<N, triple<T, U, V>>>;
    return N == 0 ? std::forward<triple_type>(t.first)  :
           N == 1 ? std::forward<triple_type>(t.second) :
           std::forward<triple_type>(t.third);
}
} // std

#include <iostream>

int main() {
    constexpr triple<int, int, int> a = {1,2,3};
    constexpr triple<int, int, int> b = a;
    static_assert(a >= b, "..");
}