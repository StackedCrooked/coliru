#include <iostream>

struct car
{
    static const int price[4] ; // declare it
};
 
struct car2
{
    // declate with an initializer (constexpr)
    static constexpr int price[4] { 43143, 34858, 39591, 13451 } ;
};

int main()
{
    for( int p : car::price ) std::cout << p << ' ' ; std::cout << '\n' ;
    
    for( int p : car2::price ) std::cout << p << ' ' ; std::cout << '\n' ;
}

const int car::price[4] = { 43143, 34858, 39591, 13451 } ; // define 

constexpr int car2::price[4] ;  // define (without initializer)

