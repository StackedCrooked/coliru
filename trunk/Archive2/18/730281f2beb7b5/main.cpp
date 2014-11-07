#include <algorithm>
#include <iostream>

int main(int argc, char** argv) {
    int x[42][3];
    int y[42][3];
    using T = decltype(x);
    
    using std::swap;
    std::cout << noexcept(swap(x, y)) << "\n";
    std::cout << (std::is_nothrow_move_constructible<T>::value && std::is_nothrow_move_assignable<T>::value) << '\n';

    return 0;
}