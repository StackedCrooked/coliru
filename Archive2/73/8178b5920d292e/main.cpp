#include <iostream>

int *b = new int(10);
const volatile int *a = dynamic_cast<const volatile int*>(b);
    
int main()
{
}