#include <iostream>
#include <climits>

int b = INT_MAX + 1; //warning: overflow in expression; result is -2147483648 
                     //with type 'int' [-Winteger-overflow]

unsigned int a = INT_MAX + 1; //OK
int main()
{
    std::cout << b << std::endl << a;
}