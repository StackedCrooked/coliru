#include <iostream>

template < typename T, typename U, template<typename,typename> class C >
struct S { S() { std::cout << "S<T,U,C> generalization: " ; C<T,U> cc ; } };

template < typename T, typename U, template<typename,typename> class C >
struct S< T*, U, C >
{ S() { std::cout << "S<T*,U,C> partial specialization: " ; const C<T*,U> cc ; } };

template < typename T, typename U, template<typename,typename> class C >
struct S< T*, U*, C >
{ S() { std::cout << "S<T*,U*,C> partial specialization: " ; C<T*,U*> cc ; } };

template < typename U, template<typename,typename> class C >
struct S< int, U, C >
{ S() { std::cout << "S<int,U,C> partial specialization: " ; const C<short,U> cc ; } };

template < template<typename,typename> class C >
struct S< int, int, C >
{ S() { std::cout << "S<int,int,C> partial specialization: " ; C<short,short> cc ; } };

template < typename, typename > struct A
{ A() { std::cout << "generalization A<any,any>\n" ; } };

template < typename T, typename U > struct A<T*,U>
{ A() { std::cout << "partial specialization A<pointer,any>\n" ; } };

template < typename T, typename U > struct A<T*,U*>
{ A() { std::cout << "partial specialization A<pointer,pointer>\n" ; } };

template < typename U > struct A<short,U>
{ A() { std::cout << "partial specialization A<short,any>\n" ; } };

template <> struct A<short,short>
{ A() { std::cout << "complete specialization A<short,short>\n" ; } };

int main()
{
   S< char, double, A > a ;
   // S<T,U,C> generalization: generalization A<any,any>

   S< char*, double, A > b ;
   // S<T*,U,C> partial specialization: partial specialization A<pointer,any>

   S< char*, double*, A > c ;
   // S<T*,U*,C> partial specialization: partial specialization A<pointer,pointer>

   S< int, double, A > d ;
   // S<int,U,C> partial specialization: partial specialization A<short,any>

   S< int, int, A > e ;
   // S<int,int,C> partial specialization: complete specialization A<short,short>
}
