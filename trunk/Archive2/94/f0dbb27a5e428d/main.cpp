#include <iostream>
#include <string>

std::string a(int n)
{
    if (n == 0) return "";
    else a(n / 2);
}

int main()
{
    std::cout << a(5) << std::endl;
    
    return 0;
}