#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>

template<typename T>
void my_swap(T& arg1, T& arg2)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    using std::swap;
    swap(arg1, arg2);
}

template<typename T, std::size_t N>
void my_swap(T (&arg1)[N], T (&arg2)[N])
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    using std::swap;
    swap(arg1, arg2);
}

template<typename T>
void my_swap(T (&)[0], T (&)[0])
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // do nothing
}

int main() 
{
   {
       int a[0], b[0];
       my_swap(a, b);
   }
   {
       int a[10], b[10];
       my_swap(a, b);
   }
   {
       int a, b;
       my_swap(a, b);
   }
}
