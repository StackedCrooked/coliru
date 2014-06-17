#include <type_traits>
#include <stdexcept>
#include <iostream>

template<typename T>
struct kwarg {
    static_assert(std::is_copy_constructible<T>::value, "Type must be copyable");

    struct container {
        const kwarg* parent;
        const T& t;
    };

    container operator=(T&& t) const {
        return { this, std::forward<T>(t) };
    }
};

template<typename T, typename... Args>
inline T get(const kwarg<T>& kw, const typename kwarg<T>::container& ref, Args&&... args) {
    if(&kw == ref.parent) {
        return ref.t;
    }
    return get(kw, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
inline T get(const kwarg<T>& kw) {
    throw std::runtime_error("keyword argument not found");
}

template<typename T, typename... Args>
inline T get(const kwarg<T>& kw, const T& def, const typename kwarg<T>::container& ref, Args&&... args) {
    if(&kw == ref.parent) {
        return ref.t;
    }
    return get(kw, def, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
inline T get(const kwarg<T>&, const T& def) {
    return def;
}

kwarg<int> width, height;

template<typename... Args>
void f(Args&&... args) {
    auto&& w = get(width, 100, std::forward<Args>(args)...);
    auto&& h = get(height, 200, std::forward<Args>(args)...);
    std::cout << h << '\n' << w << '\n';
}

int main() {
    f(width = 300, height = 400);
}