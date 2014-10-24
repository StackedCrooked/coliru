#include <iostream>

template <class T, size_t N> constexpr size_t size(const T(&array)[N]) noexcept
{
    return N;
}

int main(){
    int a[0];
    
    std::cout << size(a);
    
    return 0;
}
