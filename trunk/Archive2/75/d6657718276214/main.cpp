#include <functional>
#include <iostream>

template < typename T, typename C > struct property // getter elided for brevity
{
    ////////////// the narrow interface is public //////////////////

    operator const T& () const& { return value ; }
    operator T () const&& { return value ; }

    property<T,C>& operator= ( const T& v )
    { if(setter) setter(v) ; else value = v ; return *this ; }

    // compound assignment operators (if required)
    // eg.
    property<T,C>& operator+= ( const T& v )
    {
        if(setter) setter(value+v) ; else value += v ;
        return *this ;
    }

    private:
        T value ;

        using setter_type = std::function< void( const T& ) > ;
        std::function< void( const T& ) > setter ;

        ////////////// the wide interface is private //////////////////

        property( T&& v ) : value( std::move(v) ) {}

        property( const T& v = T() ) : value(v) {}

        template < typename FN, typename... ARGS >
        property( const T& v, FN fn, ARGS... args ) : value(v),
                 setter( std::bind( fn, args..., std::placeholders::_1 ) ) {}

        // additional constructors (if required)

        property<T,C>( const property<T,C>& ) = default ;
        property<T,C>( property<T,C>&& ) = default ;
        property<T,C>& operator= ( const property<T,C>& ) = default ;
        property<T,C>& operator= ( property<T,C>&& ) = default ;

        ////////////// the containing class is a friend  //////////////////
        ////////////// and can access the wide interdace //////////////////
        friend C ;
};

template < typename CHAR_TYPE, typename TRAITS_TYPE, typename T, typename C >
std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>&
operator << ( std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>& stm, 
              const property<T,C>& prop ) { return stm << T(prop) ; }

#include <string>

struct A
{
    property<std::string,A> name{ "anonymous", &A::set_name, this, 3 };

    property<double,A> amount{ 12.3, &A::set_amount, this } ;

    private:
        void set_amount( double d )
        { /* validate */ amount.value = d ; std::cout << "set_amount\n" ; }

        void set_name( int excl, std::string new_name )
        {
            /* validate */
            name.value = new_name + std::string( excl, '!') ;
            std::cout << "set_name\n" ;
        }
};

int main()
{
    A a ;
    std::cout << a.name << ' ' << a.amount << '\n' ;

    a.name = "Cambalinho" ;
    a.amount += 567.89 ;

    std::cout << a.name << ' ' << a.amount << '\n' ;

    #ifdef TRY_BYPASS_SETTER
        decltype(a.amount) my_value(1234) ; // ***error: constructor is private
        std::swap( a.amount, my_value ) ; // ***error: move constructor is private
    #endif // TRY_BYPASS_SETTER
}
