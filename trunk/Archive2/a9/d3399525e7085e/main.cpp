#include <algorithm>
#include <iostream>

int main()
{
    char[] a = "banane";
    char[] b = "banana";
    
    std::cout << std::equal(a, a+5, b, b+5) << std::endl;
    
    return 0;
}