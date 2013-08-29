#include <utility>
#include <type_traits>

template<typename From, typename To>
using Convert = std::is_convertible<From,To>;

template<typename T>
using NoThrowMove = std::is_nothrow_move_assignable<T>;

template<typename T, typename U, typename V>
struct triple {
    using first_type = T;
    using second_type = U;
    using third_type = V;

    T first;
    U second;
    V third;

    constexpr triple() = default;
    constexpr triple(const T& a, const U& b, const V& c): first(a), second(b), third(c) {}

    template<typename T2, 
             typename U2, 
             typename V2,
             class = typename std::enable_if<Convert<T2,T>::value && 
                                             Convert<U2,U>::value && 
                                             Convert<V2,V>::value
                                             >::type>
    constexpr triple(const triple<T2,U2,V2>& t): 
        first(t.first), second(t.second), third(t.third) {}

    triple& operator=(const triple& t) {
        first = t.first;
        second = t.second;
        third = t.third;
        return *this;
    }

    triple& operator=(triple&& t) noexcept(NoThrowMove<T>::value && NoThrowMove<U>::value && NoThrowMove<V>::value) {
        first = std::forward<T>(t.first);
        second = std::forward<U>(t.second);
        third = std::forward<V>(t.third);
        return *this;
    }

    void swap(triple& t) noexcept(noexcept(std::swap(first,t.first)) &&
                                  noexcept(std::swap(second,t.second)) &&
                                  noexcept(std::swap(third,t.third))) {
        using std::swap;
        swap(first,t.first);
        swap(second,t.second);
        swap(third,t.third);
    }


    triple(const triple&) = default;
    triple(triple&&) = default;

    // Operator overloads
    inline constexpr bool operator==(const triple& t) const {
        return first == t.first && second == t.second && third == t.third;
    }

    inline constexpr bool operator!=(const triple& t) const {
        return !(this->operator==(t)); // lol
    }

    inline constexpr bool operator<(const triple& t) const {
        return first < t.first ? true :
           t.first < first ? false :
           second < t.second ? true :
           t.second < second ? false :
           third < t.third;
    }

    inline constexpr bool operator<=(const triple& t) const {
        return !(t < (*this));
    }

    inline constexpr bool operator>(const triple& t) const {
        return (t < (*this));
    }

    inline constexpr bool operator>=(const triple& t) const {
        return !(this->operator<(t)); // lol again
    }
};
#include <iostream>

int main() {
    triple<int,int,int> v = {1,2,3};
    std::cout << v.first << ' ' << v.second <<  ' ' << v.third;
}