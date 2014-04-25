#include <iostream>

template <int* P>
constexpr int* f() { return P; }

int main () {
    // static_assert(static_cast<bool>(f<(int*)42>()), "fail");
    
    std::cout << f<(int *)42>() << std::endl;
    
    return (0);
}