#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

void print_range(long* begin, long* end)
{
    for(; begin != end; ++begin)
        std::cout << std::setw(2) << *begin << " ";
}

int main()
{
    long ar[]= {1, 4, 34, 1, 4, 67, 15 ,3 ,2 ,1, 34};
    int n = sizeof(ar)/sizeof(*ar);
    
    std::sort(ar, ar+n);
    print_range(ar, ar+n);
    std::cout << "// after sorting\n";
    
    int size;
    
    for(int i = 0; i < 2; ++i)
    {
        size = std::unique(ar, ar+n) - ar;
        print_range(ar, ar+n);
        std::cout << "// after calling unique\n";
        std::cout << size << " // size\n";
    }
}