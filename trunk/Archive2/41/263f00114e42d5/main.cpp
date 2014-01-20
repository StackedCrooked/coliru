#include <iostream>
#include <iomanip>
#include <limits>
#include <type_traits>

static constexpr float inf = std::numeric_limits<float>::infinity() ;

template < int N, int D = 1 > struct rational
{
    static constexpr float value = float(N) / D ;
    static constexpr int numerator = N ;
    static constexpr int denominator = D ;
};

template < int N > struct rational<N,0>
{
    static constexpr float value = inf ;
    static constexpr int numerator = 1 ;
    static constexpr int denominator = 0 ;
};

namespace detail_
{
    template < typename T >
    constexpr T pow( T x, std::size_t n ) {  return n ? x * pow( x, n-1 ) : 1 ; }

    constexpr int numerator_of( float f, std::size_t p = 0 )
    {
        return f==inf? 1 : f<0 ? -numerator_of( -f, p ) :
                                  f == int(f) ? f : numerator_of( f*10, p+1 ) ;
    }

    constexpr int denominator_of( float f, std::size_t p = 0 )
    { return f==inf? 0 : f == int(f) ? pow( 10, p ) : denominator_of( f*10, p+1 ) ; }
}

#define RATIONAL(f) rational< detail_::numerator_of(f), detail_::denominator_of(f) >

template < typename F > void test()
{ std::cout << F::value << " (" << F::numerator << '/' << F::denominator << ")\n" ; }

#define TEST(f) ( ( std::cout << std::setw(12) << #f << " => " ), test< RATIONAL(f) >() )

int main()
{
    using ten = std::integral_constant< int, RATIONAL(10.0)::numerator > ;
    std::cout << std::fixed << std::setprecision( ten::value ) ;

    // looks fine
    TEST(0.17875) ;
    TEST(-235.19) ;
    TEST(inf/100.0) ;

    // these don't look so good
    TEST(0.2/3.0) ; // fine
    constexpr float f = 0.02/3.0 ;
    // TEST(f) ; // ** error: overflow (platform dependant)

    TEST(1000.1001) ;
    TEST(1000.10009) ;
    TEST(1000.10008) ;
    TEST(1000.10007) ;
    TEST(1000.10006) ;
    TEST(1000.10005) ;
    TEST(1000.100049) ;
    TEST(1000.1000001) ;
}

void foo( RATIONAL(1000.10008) ) {}

void foo( RATIONAL(1000.100059) ) {} // is this a valid overload? (depends on the platfom)

// void foo( RATIONAL(1000.100061) ) {} // what about this? (depends on the platfom)

void bar( RATIONAL(1000.100079) ) {}

void baz() { bar( RATIONAL(1000.100081){} ) ; } // would this compile? (depends on the platfom)
