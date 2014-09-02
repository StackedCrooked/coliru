#include <iostream>
#include <type_traits>
#include <limits>
#include <bitset>

template < std::size_t NFLAG_BITS, typename UINT_TYPE = unsigned long long >
struct flagged_unsigned
{
    static_assert( std::is_same<UINT_TYPE,unsigned long>::value ||
                   std::is_same<UINT_TYPE,unsigned long long>::value,
                   "unsupported integer type" ) ;

    static constexpr std::size_t NBITS = std::numeric_limits<UINT_TYPE>::digits ;
    static_assert( NFLAG_BITS < NBITS, "too many flag bits" ) ;

    static constexpr std::size_t NVALUE_BITS = NBITS - NFLAG_BITS ;
    static constexpr UINT_TYPE FLAGS_MASK = UINT_TYPE(-1ULL) << NVALUE_BITS ;
    static constexpr UINT_TYPE VALUE_MASK = UINT_TYPE(-1ULL) >> NFLAG_BITS ;
    static constexpr bool is_unsigned_long = std::is_same< UINT_TYPE, unsigned long >::value  ;

    void operator& () const = delete ;
    UINT_TYPE to_uint_type() const { return is_unsigned_long ? bits.to_ulong() : bits.to_ullong() ; }

    flagged_unsigned( UINT_TYPE value = 0, std::bitset<NFLAG_BITS> flags = {} )
    {
        bits = value ;
        bits |= ( UINT_TYPE( flags.to_ullong() ) << NVALUE_BITS ) ;
    }

    template < std::size_t N > bool flag() const
    {
        static_assert( N < NFLAG_BITS, "no flag with this id" ) ;
        return bits[ NBITS - 1 - N ] ;
    }

    template < std::size_t N > void flag( bool b )
    {
        static_assert( N < NFLAG_BITS, "no flag with this id" ) ;
        bits[ NBITS - 1 - N ] = b ;
    }

    std::bitset<NFLAG_BITS> flags() const
    { return ( to_uint_type() & FLAGS_MASK ) >> NVALUE_BITS ; }

    operator UINT_TYPE () const { return to_uint_type() & VALUE_MASK ; }

    flagged_unsigned& operator= ( UINT_TYPE value )
    {
        bits = ( to_uint_type() & FLAGS_MASK ) | ( value & VALUE_MASK ) ;
        return *this ;
    }

    // TODO: overload other integer operations on lvalues += etc.

    private: std::bitset<NBITS> bits ;
};

template < std::size_t NFLAG_BITS, typename UINT_TYPE >
std::ostream& operator<< ( std::ostream& stm, flagged_unsigned<NFLAG_BITS,UINT_TYPE> v )
{ return stm << "( flags: " << v.flags() << " value: " << UINT_TYPE(v) << " )" ; }

int main()
{
    flagged_unsigned<4> a = { 0x123456789abcdef, 3 } ;
    std::cout << std::hex << std::showbase << a << '\n' // ( flags: 0011 value: 0x123456789abcdef )
              << std::boolalpha << a.flag<1>() << '\n' // false
              << a.flag<2>() << '\n' // true
              << a.flags() << '\n' ; // 0011

    a.flag<0>(true) ;
    std::cout << a << '\n' ; // ( flags: 1011 value: 0x123456789abcdef )

    a = 0x1a2b3c4d5e6f ;
    std::cout << a << '\n' ; // ( flags: 1011 value: 0x1a2b3c4d5e6f )

    unsigned long long b = a ;
    std::cout << b << '\n' ; // 0x1a2b3c4d5e6f

    a = a + 4095 ;
    std::cout << a << '\n' ; // ( flags: 1011 value: 0x1a2b3c4d6e6e )
}
