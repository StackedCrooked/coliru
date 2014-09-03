#include <type_traits>
#include <utility>
#include <array>

template<class... T>
constexpr std::array<typename std::common_type<T...>::type, sizeof...(T)> make_array(T&&... t) {
    return {{ std::forward<T>(t)... }};
}

template<class CT, class... T>
constexpr std::array<CT, sizeof...(T)> make_array(T&&... t) {
    return {{ static_cast<CT>(std::forward<T>(t))... }};
}


int main(int argc, char **argv) {    
    auto x = make_array(3, 2.); 
    auto y = make_array<int>(3, 2.);
    
    return 0;
}
