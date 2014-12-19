#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct A
{
    bool has_to_be_removed( int a ) const { return a > value ; }
    
    struct binder 
    {
        explicit binder( A& aa ) : a(aa) {}
        bool operator() ( int v ) const { return a.has_to_be_removed(v) ; }
        const A& a ;
    };

    int value = 10 ;

    std::vector<int> my_vector { 23, 7, 2, 78, 45, 34, 7, 4, 9, 22, 38 } ;

    void test_it()
    {
        for( int v : my_vector ) std::cout << v << ' ' ; std::cout << '\n' ;

        my_vector.erase( std::remove_if( my_vector.begin(), my_vector.end(), binder(*this) ),
                         my_vector.end() ) ;

        for( int v : my_vector ) std::cout << v << ' ' ; std::cout << '\n' ;
    }
};

int main()
{
    A a ;
    a.test_it() ;
}
