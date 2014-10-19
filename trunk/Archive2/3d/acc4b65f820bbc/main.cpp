#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

int main()
{
    boost::multiprecision::cpp_int number = 1 ;
    for( int i = 2 ; i < 48 ; ++i ) number *= i ;
    std::cout << "47! == " << number << '\n' ;
}
