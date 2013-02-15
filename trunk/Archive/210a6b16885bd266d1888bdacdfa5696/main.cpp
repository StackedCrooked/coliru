// vector::emplace
#include <iostream>
#include <vector>

template <typename T>
unsigned int print(unsigned int n, const T& val)
{    
    std::cout << n << ": =" << val << std::endl;
    return n;
}

unsigned int nothing(unsigned int n)
{
    return n;
}
/*
template <typename T, typename... Args>
void print_helper(unsigned int n, const T& t, const Args&... args)
{
    print_helper(n, args...);
}
*/
template <typename... Args>
void TestVariadic(const Args&... args)
{
    unsigned int n = 0;
    n = (nothing(args)...);
    //(print<Args>(n, args)...);
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p);

  return 0;
}