#include <iostream>
#include <random>
#include <cstdint>
#include <ctime>

struct mt19937_16 : private std::mt19937
{
    using result_type = std::uint_fast16_t ;

    using std::mt19937::seed ;
    using std::mt19937::discard ;
    // more using ... (if required)

    explicit mt19937_16( std::uint_fast32_t s ) : std::mt19937(s) {}
    template< typename SEED_SEQUENCE > explicit mt19937_16( SEED_SEQUENCE& ss ) : std::mt19937(ss) {}


    static constexpr result_type min() { return 0 ; }
    static constexpr result_type max() { return 0xffff ; }

    result_type operator()() { return narrow( base() ) ; }

    private:
        std::mt19937& base() { return *this ; }
        const std::mt19937& base() const { return *this ; }

        static std::uniform_int_distribution<std::uint_fast16_t> narrow ;

    friend bool operator== ( const mt19937_16& a, const mt19937_16& b )
    { return a.base() == b ; }
    friend bool operator!= ( const mt19937_16& a, const mt19937_16& b )
    { return !( a == b ) ; }

    template< typename C, typename T >
    friend std::basic_ostream<C,T>& operator<< ( std::basic_ostream<C,T>& stm, const mt19937_16& mt16 )
    { return  stm << mt16.base() ; }

    template< typename C, typename T >
    friend std::basic_istream<C,T>& operator>> ( std::basic_istream<C,T>& stm, mt19937_16& mt16 )
    { return  stm >> mt16.base() ; }
};

std::uniform_int_distribution<std::uint_fast16_t> mt19937_16::narrow( 0, 0xffff ) ; // in the implementation file (cpp)

int main()
{
    mt19937_16 twister16( std::time(nullptr) ) ;

    for( int i = 0 ; i < 10 ; ++i ) std::cout << twister16() << '\n' ;

    std::normal_distribution<double> normal( 100.0, 25.0 ) ;
    for( int i = 0 ; i < 10 ; ++i ) std::cout << normal(twister16) << '\n' ;
}
