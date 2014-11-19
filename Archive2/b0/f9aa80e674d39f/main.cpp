#include <type_traits>
#include <stdexcept>
#include <iostream>

template<typename T>
struct kwarg {
    static_assert(std::is_copy_constructible<T>::value, "Type must be copyable");

    kwarg () = default; // implicitly constexpr

    struct container {
        container () = default; // implicitly constexpr
        
        const kwarg* parent;
        const T& t;
    };

    constexpr container operator=(T&& t) const {
        return { this, std::forward<T>(t) };
    }
};

template<typename T, typename... Args>
constexpr inline T get(const kwarg<T>& kw, const typename kwarg<T>::container& ref, Args&&... args) {
    return &kw == ref.parent ? ref.t : get(kw, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr inline T get(const kwarg<T>& kw) {
   return &kw == nullptr ? T{} : throw std::runtime_error("keyword argument not found");
}

template<typename T, typename... Args>
constexpr inline T get(const kwarg<T>& kw, const T& def, const typename kwarg<T>::container& ref, Args&&... args) {
    return &kw == ref.parent ? ref.t : get(kw, def, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr inline T get(const kwarg<T>&, const T& def) {
    return def;
}

constexpr kwarg<int> width {}, height {};

template<typename... Args>
constexpr int f(Args&&... args) {
    return get(width, 100, std::forward<Args>(args)...) * get(height, 200, std::forward<Args>(args)...);
}

int main() {
    int constexpr value = f(width = 300, height = 400);
    static_assert (value == 300*400, "!!");
}