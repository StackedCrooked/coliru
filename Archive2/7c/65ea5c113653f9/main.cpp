#include <functional>
#include <iostream>

template<typename T>
struct store_const_t {
    const T& value;
    
    T operator()() const noexcept {
        return value;
    }
};

template<typename T>
constexpr store_const_t<T> make_const(const T& t) {
    return { t };
}

int main() {
    std::function<int(void)> caller = make_const(42);
    std::function<int(void)> stuff = std::move(caller);
    std::cout << stuff() << '\n';
}