#include <iostream>

namespace detail_
{
    template < typename T > struct restricted_
    {
        operator const T& () const { return value ; } // readonly

        protected:
            T value ;

            T& operator()() { return value ; } // writeable by friends

            explicit restricted_( const T& v = T() ) : value(v) {}
            restricted_( const restricted_<T>& ) = default ;
            restricted_( restricted_<T>&& ) = default ;
    };

    template < typename T, typename... F > class allow_ ;

    template < typename T, typename FRIEND >
    struct allow_<T,FRIEND> : virtual restricted_<T> { friend FRIEND ; };

    template < typename T, typename FRIEND, typename... MORE_FRIENDS >
    struct allow_<T,FRIEND,MORE_FRIENDS...> : allow_<T,FRIEND>, allow_<T,MORE_FRIENDS...> {} ;
}

template < typename T, typename... FRIENDS > struct readonly : detail_::allow_<T,FRIENDS...>
{ readonly( const T& v = T() ) : detail_::restricted_<T>(v) {} } ;

struct B ;

struct A
{
    // readable by everyone
    // writeable only by members and friends odf classes A and B
    readonly< int, A, B > x = 23 ;

    void foo() { x() = x + 5 ; }
};

struct B
{
    void foo( A& a ) { { a.x() = a.x * a.x ; } } // fine, B is a friend of a.x
};

struct X
{
    int foo( const A& a ) { return a.x ; } // fine; readable

    void bar( A& a, int v ) { a.x = v ; } // *** error: use of deleted function

    void baz( A& a, int v ) { a.x() = v ; } // *** error: a.x() is inaccesssible

};
