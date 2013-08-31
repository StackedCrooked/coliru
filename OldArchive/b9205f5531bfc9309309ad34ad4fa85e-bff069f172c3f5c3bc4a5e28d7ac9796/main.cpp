#include <iostream>
#include <type_traits>

template<typename T>
using RemoveRef = typename std::remove_reference<T>::type;

namespace detail {
struct nothing_t {};
template<typename T, typename U>
struct maybe_traits {
    static bool eq(const T& lhs, bool lhs_state, const U& rhs, bool rhs_state) {
        return (lhs_state && rhs_state && (lhs == rhs)) || (!lhs_state && !rhs_state);
    }
    static bool lt(const T& lhs, bool lhs_state, const U& rhs, bool rhs_state) {
        return rhs_state && (!lhs_state || lhs < rhs);
    }
};

template<typename T>
struct maybe_traits<T, nothing_t> {
    static bool eq(const T& lhs, bool lhs_state, const nothing_t& rhs, bool rhs_state) {
        return !lhs_state;
    }
    static bool lt(const T& lhs, bool lhs_state, const nothing_t& rhs, bool rhs_state) {
        return false;
    }
};

template<typename U>
struct maybe_traits<nothing_t, U> {
    static bool eq(const nothing_t& lhs, bool lhs_state, const U& rhs, bool rhs_state) {
        return !rhs_state;
    }
    static bool lt(const nothing_t& lhs, bool lhs_state, const U& rhs, bool rhs_state) {
        return rhs_state;
    }
};

template<>
struct maybe_traits<nothing_t, nothing_t> {
    static bool eq(const nothing_t& lhs, bool lhs_state, const nothing_t& rhs, bool rhs_state) {
        return true;
    }
    static bool lt(const nothing_t& lhs, bool lhs_state, const nothing_t& rhs, bool rhs_state) {
        return false;
    }
};
} // detail

template<typename>
struct maybe;

template<typename T>
struct maybe {
private:
    T value;
    bool active;
public:
    using value_type = T;
    constexpr maybe() noexcept: active(false) {}
    maybe(const maybe& o) noexcept: value(o.value), active(o.active) {}    
    maybe(maybe&& o) noexcept: value(std::move(o.value)), active(std::move(o.active)) {}
    explicit maybe(T value) noexcept: value(std::move(value)), active(true) {}

    maybe& operator=(const maybe& o) {
        value = o.value;
        active = o.active;
        return *this;
    }
    
    maybe& operator=(maybe&& o) {
        value = o.value;
        active = o.active;
        o.value = T();
        o.active = false;
        return *this;
    }
        
    explicit operator bool() {
        return active;
    }

    template<typename U>
    bool operator==(const maybe<U>& rhs) const {
        return detail::maybe_traits<T, U>::eq(value, active, rhs.data(), rhs.state());
    }

    template<typename U>
    bool operator!=(const maybe<U>& rhs) const {
        return !(*this == rhs);
    }

    template<typename U>
    bool operator<(const maybe<U>& rhs) const {
        return detail::maybe_traits<T, U>::lt(value, active, rhs.data(), rhs.state());
    }

    template<typename U>
    bool operator<=(const maybe<U>& rhs) const {
        return !(rhs < *this);
    }

    template<typename U>
    bool operator>=(const maybe<U>& rhs) const {
        return !(*this < rhs);
    }

    template<typename U>
    bool operator>(const maybe<U>& rhs) const {
        return rhs < *this;
    }

    T operator*() const {
        if(!active)
            throw "...";
        return value;
    }

    T data() const {
        return value;
    }

    bool state() const {
        return active;
    }
};

template<typename T>
inline maybe<RemoveRef<T>> just(T&& value) {
    return maybe<RemoveRef<T>>{std::forward<T>(value)};
}

constexpr auto nothing = maybe<detail::nothing_t>();

int main() {
    maybe<int> q(1);
    maybe<int> x;
    std::cout << std::boolalpha;
    std::cout << (q != nothing) << ' ' << (nothing != q) << ' ';
    std::cout << (x != q) << ' ' << (q != x) << ' ' << (q == q);
    std::cout << ' ' << (q == just(1)) << ' ' << (just(1) == q);
    std::cout << ' ' << (x == x) << ' ' << (x == nothing) << ' ';
    std::cout << ' ' << (nothing == x);
}