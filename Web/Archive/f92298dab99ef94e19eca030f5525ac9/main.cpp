// vector::emplace
#include <iostream>
#include <vector>
#include <utility>
#include <cstdarg>

int size_calculator(size_t nArgCount, ...)
{
    if (!nArgCount)
        return 0;
    
    unsigned int i = 0;
    int sum = 0;
    
    printf("# of Arguments = %lu, Sizes are:\n\t", nArgCount);
    
    va_list marker; 
    va_start( marker, nArgCount ); /* Initialize variable arguments. */ 
    
    while( i++ < nArgCount )
    { 
        int nSize = va_arg( marker, int);
        printf("Arg # %u size = %d, ", i, nSize);
        sum += nSize;
    }
    va_end( marker ); /* Reset variable arguments. */ 
    puts("");
    return sum;
}

template <typename T>
int report_size(const T& val)
{
    //std::cout << "sizeof value:" << sizeof(val) << std::endl;
    //printf("sizeof(T) = %lu\n", sizeof(val));
    return sizeof(val);
}
/* Template specialization */
template <>
int report_size(const int& val)
{
    //std::cout << "sizeof int value:" << sizeof(val) << std::endl;
    //printf("sizeof(int) = %lu\n", sizeof(val));
    return sizeof(val);
}

/* Overloaded printFmt's */
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
    auto n = size_calculator(sizeof...(args), report_size<Args>(args)...);
    printf("Total from size_calculator(): %d\n\n", n);
    
    printf("sizeof...(args): %lu, vs sizeof...(Args): %lu\n\n", sizeof...(args), sizeof...(Args));
    //int n = 1 + (0, report_size<Args>(args)..., 4);
    //print_helper(1, report_size<Args>(args)...);
    print_helper(1, args...);
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p, "string");

  return 0;
}