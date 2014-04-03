#include <iostream>

int main() 
{
    int a=1, b;
    
    b = ++a + ++a + ++a;
    
    std::cout<<b;
}