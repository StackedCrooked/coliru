#include <type_traits>
#include <utility>

template<typename T>
constexpr T add(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename... Args>
constexpr typename std::common_type<T, Args...>::type add(T&& t, Args... args) {
    return std::forward<T>(t) + add(args...);
}

int main() {
    static_assert(add(1,2,3) == 6, "..");
}