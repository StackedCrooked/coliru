#include <array>
#include <algorithm>

template<typename T, typename... I> std::array<T, sizeof...(I)> foo(I... args) {
    auto list = { args... };
    std::array<T, sizeof...(I)> xs;
    std::copy(list.begin(), list.end(), xs.begin());
    return xs;
}

template<typename T, typename... I> std::array<T, sizeof...(I)> bar(I... args) {
    return std::array<T, sizeof...(I)> { args... };
}

int main()
{
    auto a = foo<int>(1,2,3);
    auto b = bar<int>(1,2,3);
    
    return 0;
}
