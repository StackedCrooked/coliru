#include <cmath>
#include <type_traits>

template<typename T>
void force_stack() {
    static_assert(std::is_same<T, int>::value, "...");
}

int main() {
    auto c = std::abs(-1);
    force_stack<decltype(c)>();    
}