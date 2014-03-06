#include <iostream>
#include <utility>

namespace detail__ { template < typename A, typename B > struct helper ; }

template < typename A, typename B > struct temp
{
    temp( const A& a, const B& b ) : p(a,b) {}

    // ...

    private: std::pair<A,B> p ;

    // ...

    friend std::ostream& operator<< ( std::ostream& stm, const temp<A,B>& t )
    { return detail__::helper<A,B>::help( stm, t ) ; }

    friend detail__::helper<A,B> ; // if required
};

namespace detail__
{
    template < typename A, typename B > struct helper
    {
        static std::ostream& help( std::ostream& stm, const temp<A,B>& )
        { return stm << "generalisation<A,B>" ; }
    };

    template < typename A > struct helper<A,const char*>
    {
        static std::ostream& help( std::ostream& stm, const temp<A,const char*>& )
        { return stm << "specialisation<A,const char*>" ; }
    };

    template < typename B > struct helper<const char*,B>
    {
        static std::ostream& help( std::ostream& stm, const temp<const char*,B>& )
        { return stm << "specialisation<const char*,B>" ; }
    };

    template <> struct helper<const char*,const char*>
    {
        static std::ostream& help( std::ostream& stm, const temp<const char*,const char*>& )
        { return stm << "specialisation<const char*,const char*>" ; }
    };
}

int main()
{
    temp<int,int> a( 1, 2 ) ;
    std::cout << a << '\n' ; // generalisation<A,B>

    temp<int,const char*> b( 1, "abc" ) ;
    std::cout << b << '\n' ; // specialisation<A,const char*>

    temp<const char*,double> c( "efgh", 8.3 ) ;
    std::cout << c << '\n' ; // specialisation<const char*,B>

    temp<const char*,const char*> d( "ijkl", "mnop" ) ;
    std::cout << d << '\n' ; // specialisation<const char*,const char*>
}
