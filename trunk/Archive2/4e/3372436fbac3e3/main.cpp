#include <iostream>
#include <cstdlib>

int x = rand();
int i;

int& foo() { return i; }

void bar(int& ref = x%2 ? foo() : (std::cin >> i, i) )
{
    std::cout << ref;   
}

int main()
{
    bar();
}