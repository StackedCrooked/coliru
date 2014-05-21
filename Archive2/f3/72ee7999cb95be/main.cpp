#include <iostream>
#include <cstdlib>

int x = (srand(time(0)), rand());
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