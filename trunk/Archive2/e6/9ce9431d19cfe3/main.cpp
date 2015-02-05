#include <cstddef>
#include <iostream>
int main()
{
    std::cout<<"Hello"<<"\n";
    const std::size_t N = 100;
    int* a = new int[N];
    for(std::size_t n = 0; n<N; ++n)
        a[n] = n;
    delete[] a;
}