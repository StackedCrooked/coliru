#include <iostream>
int main()
{
    char c = 2;
    unsigned int un = 2;
    int  n = -10;
    std::cout <<  " 2 + (-10), where 2 is a char    = " << c + n << '\n'
              <<  " 2 + (-10), where 2 is unsigned  = " << un + n << '\n'
              <<  " -10 - 2.12  = " << n - 2.12 << '\n';
 
    char a[4] = {'a', 'b', 'c', 'd'};
    char* p = &a[1];
    std::cout << "Pointer addition examples: " << *p << *(p + 2)
              << *(2 + p) << *(p - 1) << '\n';
    char* p2 = &a[4];
    std::cout << "Pointer difference: " << p2 - p << '\n';
}