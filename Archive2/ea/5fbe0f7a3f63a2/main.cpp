#include <iostream>
#include <functional>
#include <list>

using function_list_type =  std::list< std::function< void() > > ;
static function_list_type function_list ;

template < typename CALLABLE, typename... ARGS >
function_list_type::iterator push_func( CALLABLE&& fn, ARGS&&... args )
{
    function_list.emplace_back( std::bind( std::forward<CALLABLE>(fn),
                                           std::forward<ARGS>(args)... ) );
    auto end = function_list.end() ;
    return --end ;
}

void call_forward( function_list_type::iterator iter )
{
    const auto& fn = *iter ;
    fn() ;
}

void func_1( int a, double u )
{ std::cout << "func1 - a: " << a << ", u:" << u << '\n' ; }

struct some_class
{
    int mem_fun( int a, int b, int c )
    {
        std::cout << "some_class::mem_fun - this: " << this
                  << ", a: " << a << ", b:" << b << ", c:" << c <<'\n' ;
        return v + a -b + c ;
    }
    int v = 0 ;
};

int main()
{
    int f1_a = 0 ;
    double f1_b = 0 ;
    auto f1 = push_func( func_1, std::ref(f1_a), std::ref(f1_b) ) ;

    some_class object ;
    some_class* scmf_this = std::addressof(object) ;
    int scmf_a = 0, scmf_b = 0, scmf_c = 0 ;
    auto scmf = push_func( &some_class::mem_fun, scmf_this,
                           std::ref(scmf_a), std::ref(scmf_b), std::ref(scmf_c) ) ;

    call_forward(f1) ;
    call_forward(scmf) ;
    std::cout << "-----------\n" ;

    f1_a = 23 ;
    f1_b = 67.89 ;
    call_forward(f1) ;

    scmf_a = scmf_b = scmf_c = 999 ;
    call_forward(scmf) ;
}
