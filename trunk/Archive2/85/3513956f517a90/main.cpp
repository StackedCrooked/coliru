
template<typename T, typename U>
constexpr auto Min(T&& lhs, U&& rhs) {
    return lhs < rhs ? std::forward<T>(lhs) : std::forward<U>(rhs);
}

template<typename T, typename U>
constexpr decltype(auto) Min(T& lhs, U& rhs) {
    return lhs < rhs ? lhs : rhs;
}

template<typename T, typename U>
constexpr auto Max(T&& lhs, U&& rhs) {
    return lhs < rhs ? std::forward<T>(rhs) : std::forward<U>(lhs);
}

template<typename T, typename U>
constexpr decltype(auto) Max(T& lhs, U& rhs) {
    return lhs < rhs ? rhs : lhs;
}
