#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>

struct A{
    A() { std::cout << "A default constructor" << std::endl; }
    ~A() { std::cout << "A destructor" << std::endl; }
    A( const A& ) { std::cout << "A copy constructor" << std::endl; }
    A( A&& ) { std::cout << "A move constructor" << std::endl; }
};
struct B{
    B() { std::cout << "B default constructor" << std::endl; }
    ~B() { std::cout << "B destructor" << std::endl; }
    B( const B& ) { std::cout << "B copy constructor" << std::endl; }
    B( B&& ) { std::cout << "B move constructor" << std::endl; }
};
struct C{
    C() { std::cout << "C default constructor" << std::endl; }
    ~C() { std::cout << "C destructor" << std::endl; }
    C( const C& ) { std::cout << "C copy constructor" << std::endl; }
    C( C&& ) { std::cout << "C move constructor" << std::endl; }
};
struct D{
    D() { std::cout << "D default constructor" << std::endl; }
    ~D() { std::cout << "D destructor" << std::endl; }
    D( const D& ) { std::cout << "D copy constructor" << std::endl; }
    D( D&& ) { std::cout << "D move constructor" << std::endl; }
};
struct E{
    E() { std::cout << "E default constructor" << std::endl; }
    ~E() { std::cout << "E destructor" << std::endl; }
    E( const E& ) { std::cout << "E copy constructor" << std::endl; }
    E( E&& ) { std::cout << "E move constructor" << std::endl; }
};

class Gadget
{
    struct call_setters
    {
        Gadget& self;
        call_setters( Gadget& self_ ) : self( self_ ){}
        template< typename T >
        void operator()( T& t ) const
        {
            self.set( t );
        }
    };

public:
    template< typename... Args >
    Gadget( const Args&... args )
    {
        using namespace boost::mpl;
        using namespace boost::mpl::placeholders;

        typedef vector<A, B, C, D, E> allowed_args;

        static_assert(sizeof...(Args) <= size<allowed_args>::value, "Too many arguments");

        typedef typename fold< vector<Args...>
            , set0<>
            , insert<_1, _2>
        >::type unique_args;
        static_assert(size<unique_args>::value == sizeof...(Args), "Duplicate argument types");

        typedef typename fold< allowed_args
            , int_<0>
            , if_< has_key<unique_args, _2 >, next<_1>, _1 >
        >::type allowed_arg_count;

        static_assert(allowed_arg_count::value == sizeof...(Args), "One or more argument types are not allowed");
        
        namespace bf = boost::fusion;
        bf::for_each( bf::vector<const Args&...>( args... ), call_setters{ *this } );
    }

    void set( const A& ) { std::cout << "Set A" << std::endl; }
    void set( const B& ) { std::cout << "Set B" << std::endl; }
    void set( const C& ) { std::cout << "Set C" << std::endl; }
    void set( const D& ) { std::cout << "Set D" << std::endl; }
    void set( const E& ) { std::cout << "Set E" << std::endl; }
};

int main()
{
    Gadget{ A{}, E{}, C{}, D{}, B{} };
}