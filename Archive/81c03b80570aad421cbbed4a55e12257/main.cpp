// vector::emplace
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>

void dummy(...)
{
}

template <typename T>
const T& report_size(const T& val)
{
    //std::cout << "sizeof value:" << sizeof(val) << std::endl;
    printf("sizeof(T) = %d\n", sizeof(val));
    return val;
}
template <>
const int& report_size(const int& val)
{
    //std::cout << "sizeof int value:" << sizeof(val) << std::endl;
    printf("sizeof(int) = %d\n", sizeof(val));
    return val;
}

void printFmt(int i, char val)
{
    printf("%d: = %c\n", i, val);
}

void printFmt(int i, int val)
{
    printf("%d: = %d\n", i, val);
}
void printFmt(int i, const char* val)
{
    printf("%d: = %s\n", i, val);
}

template <typename T>
int print_helper( int n, const T& val)
{    
    //std::cout << n << ": =" << val << std::endl;
    printFmt(n, val);
    return n;
}

template <typename T, typename... Args>
void print_helper(int n, const T& val, const Args&... args)
{
    //std::cout << n << ": =" << val << std::endl;
    printFmt(n, val);
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