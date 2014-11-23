#include <iostream>
#include <boost/any.hpp>
#include <functional>

int main()
{
    int i = 7 ;
    double d = 56.7 ;
    boost::any many[] { std::ref(i), &d } ;

    int& r = boost::any_cast< std::reference_wrapper<int> >( many[0] ) ;
    int* pi = &r ;
    r = 789 ;
    *pi += 32 ;
    std::cout << i << '\n' ;

    double* p = boost::any_cast<double*>( many[1] ) ;
    *p = 0.1 ;
    std::cout << d << '\n' ;
}
