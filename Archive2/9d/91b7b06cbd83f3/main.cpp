#include <iostream>

template <class T, size_t N> constexpr size_t size(const T(&array)[N]) noexcept
{
    return N;
}

template <class T> constexpr size_t size(const T& array) noexcept
{
    return 0;
}

int main(){
    int a[0];
    std::cout << size(a) << std::endl;
    
    int b[5];
    std::cout << size(b) << std::endl;
    
    return 0;
}
