#include <type_traits>
#include <stdexcept>
#include <iostream>

template<typename T>
struct kwarg {
    using value_type = T;
    constexpr kwarg(const T &t): t{t} {}
    T t;
};
struct any { template<typename T> constexpr any(T &&) {} };

template<typename K, typename... Args>
constexpr inline typename K::value_type get(any, Args&&... args) {
    return get<K>(std::forward<Args>(args)...);
}
template<typename K, typename... Args>
constexpr inline typename K::value_type get(K&& kw, Args&&... args) {
    return kw.t;
}

template<typename K>
constexpr inline typename K::value_type get_or(typename K::value_type const& def) {
    return def;
}
template<typename K, typename... Args>
constexpr inline typename K::value_type get_or(typename K::value_type const& def, any, Args&&... args) {
    return get_or<K>(def, std::forward<Args>(args)...);
}
template<typename K, typename... Args>
constexpr inline typename K::value_type get_or(typename K::value_type const& def, K&& kw, Args&&... args) {
    return kw.t;
}

struct width: kwarg<int> { using kwarg::kwarg; };
struct height: kwarg<int> { using kwarg::kwarg; };
struct depth: kwarg<int> { using kwarg::kwarg; };

template<typename... Args>
constexpr int f(Args&&... args) {
    return get_or<width>(100, std::forward<Args>(args)...) * get_or<height>(100, std::forward<Args>(args)...);
}

int main() {
    int constexpr value = f(width{300}, depth{400});
    static_assert (value == 300*100, "!!");
}