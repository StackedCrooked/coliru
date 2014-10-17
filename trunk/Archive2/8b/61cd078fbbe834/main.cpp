#include <iostream>
int main()
{
    std::cout << std::boolalpha;
    int n = -1;
 
    int n2 = 1;
    std::cout << " -1 == 1? " << (n == n2) << '\n'
              << "Comparing two signed values:\n"
              << " -1  < 1? " << (n < n2) << '\n'
              << " -1  > 1? " << (n > n2) << '\n';
 
    unsigned int u = 1;
    std::cout << "Comparing signed and unsigned:\n"
              << " -1  < 1? " << (n < u) << '\n'
              << " -1  > 1? " << (n > u) << '\n';
 
    unsigned char uc = 1;
    std::cout << "Comparing signed and smaller unsigned:\n"
              << " -1  < 1? " << (n < uc) << '\n'
              << " -1  > 1? " << (n > uc) << '\n';
}