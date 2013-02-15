#include <iostream>


namespace nonstd {
    template <typename T, size_t N>
    T* begin(T (&a)[N]) { return &a[0]; }

    template <typename T, size_t N>
    T* end(T (&a)[N]) { return a + N; }
}


int main()
{
    int a[] = {1, 2};
    nonstd::begin(a);
    std::cout << "." << std::endl;
}