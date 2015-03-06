#include <vector>
#include <array>
#include <iostream>

template <
    typename T,
    typename... Args,
    template <typename...> class C
>
void foo(C<T, Args...> const& container) {
    std::cout << "OK!\n";   
}

int main() {
    std::vector<int> test = {1, 2, 3};
    std::array<int, 3> test1 = {1, 2, 4};
    foo(test);
    foo(test1);
}