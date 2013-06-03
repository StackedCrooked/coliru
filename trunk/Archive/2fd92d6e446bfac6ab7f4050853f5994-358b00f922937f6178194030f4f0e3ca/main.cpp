#include <iostream>
#include <functional>

template<typename... T> void foo(T&&... ts) {
    // ADD SFINAE HERE IF DESIRED
    std::array<foo_t, sizeof...(T)> = { std::forward<T>(ts)... };
    
}