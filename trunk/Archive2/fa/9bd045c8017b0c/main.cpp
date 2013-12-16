#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>

#include <cstdio>

int main()
{
    using std::printf;
    
    printf("  \n  coliru doesn't print leading spaces of the first line of output...\n");
    
    printf("%4d\n", 42);
    
    printf("%4d\n", 12345);
    
    printf("%04d\n", 42);
    
    printf("%04d\n", 12345);
    
    printf("%.4f\n", 3.14);
    
    printf("%.4f\n", 3.14159);
}
