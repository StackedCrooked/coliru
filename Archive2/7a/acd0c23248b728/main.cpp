#include <cstddef>
#include <iostream>
 
int main()
{
    const std::size_t N = -100;
    int* a = new int[N];
    int* end = a + N;
    for (std::ptrdiff_t i = N; i > 0; --i)
    {
        *(end - i) = i;
        std::cout<<i<<std::endl; 
    }
    delete[] a;
}