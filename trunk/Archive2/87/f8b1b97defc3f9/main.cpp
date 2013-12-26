#include <iostream>
#include <type_traits>

enum class enabler_t {};

template<typename T>
using EnableIf = typename std::enable_if<T::value, enabler_t>::type;

//This function is chosen when an integral type is passed in
template<class T, EnableIf<std::is_integral<T>>...>
auto function(T t) {
    std::cout << "integral" << std::endl;
    return;
}

//This function is chosen when a floating point type is passed in
template<class T, EnableIf<std::is_floating_point<T>>...>
auto function(T t) {
    std::cout << "floating" << std::endl;
    return;
}

int main() {
    function(1);    //prints "integral"
    function(3.14); //prints "floating"
}