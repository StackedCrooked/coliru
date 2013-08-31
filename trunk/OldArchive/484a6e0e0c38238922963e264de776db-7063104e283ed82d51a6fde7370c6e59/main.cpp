#include <vector>
#include <type_traits>
#include <iostream>

template<typename Vec, typename T>
void push_back(Vec& vec, T&& value) {
    using value_t = typename Vec::value_type;
    static_assert(std::is_same<value_t, T>::value, "Non-matching types");
    vec.push_back(value);
}

template<typename Vec, typename T, typename... Args>
void push_back(Vec& vec, T&& value, Args&&... args) {
    using value_t = typename Vec::value_type;
    static_assert(std::is_same<value_t, T>::value, "Non-matching types");
    vec.push_back(value);
    push_back(vec,std::forward<Args>(args)...);
}

int main() {
    std::vector<int> v;
    push_back(v,1,2,3,4,5,6);
    for(auto&& i : v) {
        std::cout << i << ' ';
    }
}