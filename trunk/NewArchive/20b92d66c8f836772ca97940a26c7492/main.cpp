#include <iostream>

int main()
{
    double sum = 1.0, a = 4.0 ; 
    for(; a <= 100; a += 4)
        sum += (1/a) ;
    std::cout << "The sum is : " << sum ; 
    return 0; 
}