#include <iostream>
#include <type_traits>
 
template <typename T>
struct A {
    int val = 0;
 
    template<typename U = T, typename std::enable_if<U::value>::type...>
    A(int n) : val(n) {}
    
    A(...) {}
    /* ... */
};
 
struct YES { constexpr static bool value = true; };
struct NO { constexpr static bool value = false; };
 
int main() {
    A<YES> y(10);
    A<NO> n;
    std::cout << "YES: " << y.val << std::endl
              << "NO:  " << n.val << std::endl;
}