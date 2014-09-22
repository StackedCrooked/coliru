#include <iostream>

int main()
{
    int sum = 7 ;
    const int val = 6 ;

    std::cout << "simple assignment: " ;
    ( ( std::cout << "evaluate sum    " ), sum ) = ( ( std::cout << "evaluate sum    " ), sum ) + val ;
    // simple assignment: evaluate sum    evaluate sum

    sum = 7 ;
    std::cout << "\n\ncompound assignment: " ;
    ( ( std::cout << "evaluate sum    " ), sum ) += val ;
    // ompound assignment: evaluate sum
}
