#include <limits>
#include <utility>

template<typename T, T min = std::numeric_limits<T>::min(), 
                     T max = std::numeric_limits<T>::max()>
struct ranged_value {
private:
    T value;
public:
    constexpr ranged_value() = default;
    constexpr ranged_value(T v): value(std::move(v)) {}
    constexpr T get() const noexcept(noexcept(value > max) && noexcept(value < min)) {
        return value > max ? max : value < min ? min : value;
    }
    
    constexpr operator T() const noexcept(get()) {
        return get();
    }
};



#include <iostream>

int main() {
    ranged_value<int, 0, 100> x(104);
    std::cout << x.get();
}    