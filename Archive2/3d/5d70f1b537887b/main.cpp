#include <iostream>

template < typename T > void foo( const T& ) { std::cout << "foo - not variadic, arity one\n" ; }
template < typename T > void foo( const T&, const T& ) { std::cout << "foo - non-variadic, arity two\n" ; }

template < typename... T > void foo( const T&... ) { std::cout << "foo - variadic, arity zero or more\n" ; }
template < typename A, typename... B > void foo ( const A&, const B&... ) { std::cout << "bar - variadic, arity one or more\n" ; }

int main()
{
    foo() ; // arity zero => "foo - variadic, arity zero or more\n"
    // the only viable function is: template < typename... T > void foo( const T&... )

    foo(1) ; // arity one => foo - not variadic, arity one
    // viable functions are:
    // template < typename T > void foo( const T& )
    // template < typename... T > void foo( const T&... )
    // use partial ordering: non-variadic template is selected over the variadic template  
    // the function template specialization refers to the non-variadic template

    foo( 1, 2 ) ; // arity two => foo - not variadic, arity two
    // viable functions are:
    // template < typename T > void foo( const T&, const T& )
    // template < typename... T > void foo( const T&... )
    // template < typename A, typename... B > void foo ( const A&, const B&... )
    // use partial ordering: non-variadic template is selected over the variadic template  
    // the function template specialization refers to the non-variadic template

    foo( 1, 2, 3 ) ; // arity three => foo - not variadic, arity one or more
    // viable functions are:
    // template < typename... T > void foo( const T&... )
    // template < typename A, typename... B > void foo ( const A&, const B&... )
    // both are variadic templates
    // use partial ordering: the template with more non-variadic template parameters is selected 
    // the function template specialization refers to  template < typename A, typename... B > void foo ( const A&, const B&... )
    // caveat: AFAIK
}
