#include <string>
#include <typeinfo>

#ifdef __GNUG__

#include <cxxabi.h>
#include <cstdlib>
#include <memory>

template< typename T > std::string type_name()
{
    int status ;
    std::unique_ptr< char[], decltype(&std::free) > buffer(
        __cxxabiv1::__cxa_demangle( typeid(T).name(), nullptr, 0, &status ), &std::free ) ;
    return status==0 ? buffer.get() : "__cxa_demangle error" ;
}

#else // !defined __GNUG__

template< typename T > std::string type_name()
{
    return typeid(T).name() ;
}

#endif //__GNUG__

template< typename T > std::string type_name( const T& )
{
    return type_name<T>() ;
}

#include <type_traits>
#include <iostream>
#include <vector>

template < typename T, typename = void > struct inspector
{ void operator() () const { std::cout << type_name<T>() << '\n' ; } };

template < typename T > struct inspector<T*,void>
{ void operator() () const { std::cout << "pointer to " ; inspector<T>{}() ; } };

template < typename T > struct inspector<T&,void>
{ void operator() () const { std::cout << "lvalue reference to " ; inspector<T>{}() ; } };

template < typename T > struct inspector<T&&,void>
{ void operator() () const { std::cout << "rvalue reference to " ; inspector<T>{}() ; } };

template < typename T > struct inspector< std::vector<T>, void >
{ void operator() () const { std::cout << "vector of " ; inspector<T>{}() ; } };

template < typename T > void Inspect() { inspector<T>{}() ; }


int main()
{
   Inspect<float>() ; //  float
   Inspect<float*>() ; // pointer to float
   Inspect< std::vector<float> >() ; // vector of float
   Inspect< std::vector<float*> >() ; // vector of pointer to float
   Inspect< std::vector<float>* >() ; // pointer to vector of float
   Inspect< std::vector<float*>& >() ; // lvalue reference to vector of pointer to float
   Inspect< std::vector< std::vector<float>* >&& >() ; // rvalue reference to vector of pointer to vector of float
}

