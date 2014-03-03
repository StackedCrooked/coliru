#include <iostream>
#include <type_traits>

// ============================
using std::cout; using std::endl;
constexpr char const * const el = "\n";

// ============================
template < typename T_, typename = typename std::enable_if<std::is_enum<T_>::value>::type >
std::ostream & operator<<( std::ostream & os, T_ const & v ) {
    return os << static_cast<typename std::underlying_type<T_>::type>(v)<< " ";
}

// ============================
// Minimum support for a constexpr array because std::array::operator[] lacks constexpr
template <typename T_, size_t N_>
struct Array {
    constexpr size_t size() const { return N_; }

    constexpr T_&       operator[]( size_t i ) { return values_[i]; }
    constexpr T_ const& operator[]( size_t i ) const { return values_[i]; }

    constexpr T_*        begin()       { return values_; }
    constexpr T_*        end()         { return values_+N_; }
    constexpr T_ const * begin() const { return values_; }
    constexpr T_ const * end() const   { return values_+N_; }

    T_ values_[N_];
};

// ============================
// return a sorted copy of the array argument
template <typename T_, size_t N_>
constexpr Array<T_, N_> const_sort( Array<T_, N_> tab ) {
    Array<T_, N_> result {};
    for( size_t i{}; i != N_; ++i )
        result[i] = tab[i];

    for( size_t i{}; i != N_-1; ++i ) {
        size_t min {i};
        for( size_t j{ i+1 }; j != N_; ++j ) {
            if( result[j] < result[min] )
                min = j;
        }
        if( min != i ) {
            auto tmp    = std::move( result[i] );
            result[i]   = std::move( result[min] );
            result[min] = std::move( tmp );
        }
    }
    return result;
}

// ============================
// The user has to specialize UnsortedFunc to return an Array<EnumType,N>
template <typename T_>
constexpr auto UnsortedFunc();

// ============================
// check for existence of a matching enum member equal to an integral value.
// The user has to feed a specialization of UnsortedFunc with the enum values.
template< typename E_>
constexpr bool Contains( typename std::underlying_type<E_>::type v ) {
    constexpr auto Sorted = const_sort( UnsortedFunc<E_>() );

    using T = typename std::underlying_type<E_>::type;
    T min = static_cast<T>(Sorted[0]);
    T max = static_cast<T>(Sorted[Sorted.size()-1]);
    if ( v < min || max < v )
        return false;

    size_t low {}, high { Sorted.size() };
    while ( low < high ) {
        size_t mid = (high + low ) / 2;
        if ( v < static_cast<T>(Sorted[ mid ]) ) {
            high = mid;
        } else {
            if ( !( static_cast<T>(Sorted[ mid ]) < v ) )
                return true;
            low = mid+1;
        }
    }
    return false;
}

template < typename T_ >
void Dump() {
    for( auto & v : UnsortedFunc<T_>() )
        cout << v << " ";
    cout << el;

    for( auto & v : const_sort(UnsortedFunc<T_>()) )
        std::cout << v << " ";
    cout << el;
}

enum class Foo : int { a=5, b=2, c = 8, d = 1, e = 4, f = 9 };
template <> constexpr auto UnsortedFunc<Foo>() { 
    return Array<Foo,6>{{Foo::a, Foo::b, Foo::c, Foo::d, Foo::e, Foo::f }}; 
}

int main() {
    cout << std::boolalpha << __VERSION__ << el;

    for( auto & v : UnsortedFunc<Foo>() )
        cout << v << " ";
    cout << el;
    for( auto & v : const_sort(UnsortedFunc<Foo>()) )
        std::cout << v << " ";
    cout << el;

    constexpr bool b1 = Contains<Foo>(2);
    constexpr bool b2 = Contains<Foo>(10);

    cout << b1 << " " << b2 << el;

    for( int i{}; i != 10; ++i )
        cout << i << " : " << Contains<Foo>(i) << ", ";
}
