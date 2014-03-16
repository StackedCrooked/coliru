#include <iostream>

void swap(int *num1, int *num2)
{
    int tmp = *num2;
    *num2 = *num1;
    *num1 = tmp;
}

int main()
{
    int num1 = 5, num2 = 7 ;

    swap( &num1, &num2 ); // fine
    
    swap( num1, num2 ); // *** error
}