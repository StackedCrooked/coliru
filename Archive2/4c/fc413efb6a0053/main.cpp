#include <iostream>
#include <string>
#include <algorithm>

void print_range(long* begin, long* end)
{
    for(; begin != end; ++begin)
        std::cout << *begin << " ";
    std::cout << "\n";
}

int main()
{
    long ar[]= {1, 4, 34, 1, 4, 67, 15 ,3 ,2 ,1, 34};
    int n = sizeof(ar)/sizeof(*ar);
    
    std::sort(ar, ar+n);
    print_range(ar, ar+n);
    
    int size = std::unique(ar, ar+n) - ar;
    print_range(ar, ar+n);
    std::cout << size << std::endl; // here size =7
    
    std::cout << (int)(std::unique(ar, ar+n) - ar) << "\n"; // here we get 10!
    print_range(ar, ar+n);
}