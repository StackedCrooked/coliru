#include <stdio.h>
#include <iostream>

int main()
{
    printf("%.0f\n", 3.45); 
    printf("%.0f\n", 3.54);
    printf("%.0f\n", 3.4999999999999999);  
    int number = int(3.4999999999999999+0.5);
    std::cout << number;
}
