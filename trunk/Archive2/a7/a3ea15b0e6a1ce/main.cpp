#include <iostream>
#include <string>

void goo(int* x)
{
    *x = 1;
}

int main()
{
    int something = 6;
    
    int* a = &something;
    
    goo(a);
    
    std::cout << *a << std::endl;
}
