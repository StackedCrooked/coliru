#include <iostream>
#include <type_traits>
#include <utility>
#include <memory>

template<typename T>
using RemoveRef = typename std::remove_reference<T>::type;

namespace detail {
struct nothing_t {};
template<typename T, typename U>
struct maybe_traits {
    static bool eq(const T* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return (!lhs_state && !rhs_state) || (lhs_state && rhs_state && (*lhs == *rhs));
    }
    static bool lt(const T* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return rhs_state && (!lhs_state || *lhs < *rhs);
    }
};

template<typename T>
struct maybe_traits<T, nothing_t> {
    static bool eq(const T* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return !lhs_state;
    }
    static bool lt(const T* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return false;
    }
};

template<typename U>
struct maybe_traits<nothing_t, U> {
    static bool eq(const nothing_t* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return !rhs_state;
    }
    static bool lt(const nothing_t* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return rhs_state;
    }
};

template<>
struct maybe_traits<nothing_t, nothing_t> {
    static bool eq(const nothing_t* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return true;
    }
    static bool lt(const nothing_t* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return false;
    }
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // detail

template<typename T>
struct maybe {
private:
    std::unique_ptr<T> value;
    constexpr static bool has_nothing = std::is_same<T, detail::nothing_t>();
public:
    using value_type = T;
    constexpr maybe() noexcept {}
    explicit maybe(T value) noexcept: value(new T(value)) {}
    // explicit maybe(const T& value) noexcept: value(new T(value)) {}

    bool state() const {
        return !has_nothing && (value != nullptr);
    }

    explicit operator bool() {
        return state();
    }

    template<typename U>
    bool operator==(const maybe<U>& rhs) const {
        return detail::maybe_traits<T, U>::eq(value.get(), state(), rhs.data(), rhs.state());
    }

    template<typename U>
    bool operator!=(const maybe<U>& rhs) const {
        return !(*this == rhs);
    }

    template<typename U>
    bool operator<(const maybe<U>& rhs) const {
        return detail::maybe_traits<T, U>::lt(value.get(), state(), rhs.data(), rhs.state());
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

    T* data() const {
        return value.get();
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        value = detail::make_unique<T>(args...);
    }
};

template<typename T>
inline maybe<RemoveRef<T>> just(T&& value) {
    return maybe<RemoveRef<T>>{std::forward<T>(value)};
}

inline maybe<detail::nothing_t> nothing() {
    return {};
}

struct get_fucked {
    int in_the_butt;

    get_fucked( int a ) : in_the_butt( a ) { std::cout << "constructed\n"; };
    get_fucked(const get_fucked&) {
        std::cout << "Copied\n";
    }
    get_fucked(get_fucked&&) {
        std::cout << "Moved\n";
    }
};

int main() {
    maybe<int> q(1);
    maybe<int> x;
    maybe<get_fucked> death; // boom
    death.emplace(1);
    std::cout << std::boolalpha;
    std::cout << (x == nothing()) << ' ' << (nothing() == nothing()) << ' ';
    std::cout << (q != nothing()) << ' ' << (nothing() != q) << ' ';
    std::cout << (x != q) << ' ' << (q != x) << ' ' << (q == q);
    std::cout << ' ' << (q == just(1)) << ' ' << (just(1) == q);
}