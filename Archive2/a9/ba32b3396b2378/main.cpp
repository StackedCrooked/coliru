#include <utility>
#include <tuple>
#include <iostream>

template <class, class T>
auto dup(T &&v) {
    return std::forward<T>(v);   
}

template <class... Ts, class U>
auto test(U &&v) {
    return std::tuple<Ts...>(dup<Ts>(std::forward<U>(v))...);
}

int main() {
    auto t = test<int, char, float>(83.57);
    
    std::cout << std::get<0>(t)
       << ' ' << std::get<1>(t)
       << ' ' << std::get<2>(t)
       << '\n';
    
    return 0;
}