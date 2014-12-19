#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct A
{
    bool has_to_be_removed( int a ) const { return a > value ; }
    
    int value = 10 ;

    std::vector<int> my_vector { 23, 7, 2, 78, 45, 34, 7, 4, 9, 22, 38 } ;

    void test_it()
    {
        for( int v : my_vector ) std::cout << v << ' ' ; std::cout << '\n' ;

        my_vector.erase( std::remove_if( my_vector.begin(), my_vector.end(), 
                                         std::bind1st( std::mem_fun_ref(&A::has_to_be_removed), *this ) ),
                         my_vector.end() ) ;

        for( int v : my_vector ) std::cout << v << ' ' ; std::cout << '\n' ;
    }
};

int main()
{
    A a ;
    a.test_it() ;
}
