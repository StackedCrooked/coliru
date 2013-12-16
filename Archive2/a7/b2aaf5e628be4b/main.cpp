#include <iostream>
#include <array>


template<class T, class... A>
std::array<T, sizeof...(A)> make_array(A&&... a)
{
    return {std::forward<A>(a)...};
}

int main(int argc, char** argv) {
    auto a = make_array<int>(1, 2, 3);
    for (auto i : a)
        std::cout << i << ", ";
    return 0;
}