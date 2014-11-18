#include <iterator>
#include <iostream>

template<typename T, std::size_t N>
constexpr std::size_t size(T(&)[N]) { return N; }

int main()
{
    const int a[10]{};
    std::cout << size(a) << '\n';
}