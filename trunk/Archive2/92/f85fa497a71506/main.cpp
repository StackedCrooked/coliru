#include <iostream>

using std::cout;

int main()
{
    int a=10; 
    int const &b = a; 
    a = 11; 
    cout << a << b;    
}