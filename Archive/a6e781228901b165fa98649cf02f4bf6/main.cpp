// vector::emplace
#include <iostream>
#include <vector>
#include <utility>

void dummy(...)
{
}

template <typename T>
const T& report_size(const T& val)
{
    std::cout << "sizeof value:" << sizeof(val) << std::endl;
    return val;
}
template <>
const int& report_size(const int& val)
{
    std::cout << "sizeof int value:" << sizeof(val) << std::endl;
    return val;
}

template <typename T>
unsigned int print_helper(unsigned int n, const T& val)
{    
    std::cout << n << ": =" << val << std::endl;
    return n;
}

template <typename T, typename... Args>
void print_helper(unsigned int n, const T& val, const Args&... args)
{
    std::cout << n << ": =" << val << std::endl;
    print_helper(++n, args...);
}

template <typename... Args>
void TestVariadic(const Args&... args)
{
    dummy(report_size<Args>(args)...);
    //print_helper(1, report_size<Args>(args)...);
    print_helper(1, args...);
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p);

  return 0;
}