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

struct width: kwarg<int> { using kwarg::kwarg; };
struct height: kwarg<int> { using kwarg::kwarg; };
struct depth: kwarg<int> { using kwarg::kwarg; };

template<typename... Args>
constexpr int f(Args&&... args) {
    return get<width>(std::forward<Args>(args)...) * get<height>(std::forward<Args>(args)...);
}

int main() {
    int constexpr value = f(width{300}, height{400});
    static_assert (value == 300*400, "!!");
}