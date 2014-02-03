#include <iostream>
#include <string>
#include <vector>

#include <stdexcept>
#include <type_traits>


// The following is evil template "black magic". Only because we write it instead
// of the C++ standards committee. This is effectively a C++11 implementation of
// std::make_index_sequence which is coming in the C++14 standard

// This type exists solely to be a holder for the
// template arguments, which is a sequence of ints
template <unsigned...> struct NumberSequence {};

// Let's make a special template struct who only exists
// to construct a new NumberSequence type, given N
template <unsigned N, unsigned StartIndex, unsigned CurrentNumber, unsigned... TrailingNumbers>
struct GenerateNumberSequence
{
    // A bit of recursion, our bread and butter for variadic templates. Notice
    // that we pass 5 arguments, instead of the 4 defined above. Effectively this
    // extends the length of the template argument list by 1 every time this recursion
    // happens. So we'll need to stop it once we reach CurrentNumber == StartIndex or
    // we may go on forever until the compiler craps out due to recursion depth. Note
    // that we're also recursively redefining the 'type' to be the next level down in
    // the recursion, so that eventually this top level type is typdef'd to the bottom.
    typedef typename GenerateNumberSequence<N, StartIndex, CurrentNumber - 1, CurrentNumber, TrailingNumbers...>::type type;
};

// Now we partially specialize the template for the case where
// CurrentNumber == StartIndex, which we use to stop infinite recursion
template <unsigned N, unsigned StartIndex, unsigned... TrailingNumbers>
struct GenerateNumberSequence<N, StartIndex, StartIndex, TrailingNumbers...>
{
    // The final type def, a NumberSequence from StartIndex to N
    typedef NumberSequence<StartIndex, TrailingNumbers...> type;
};


// A helper template for generating 0...N
template <unsigned N>
struct GenerateFullNumberSequence
    : GenerateNumberSequence<N, 0, N>
{
};

// A helper for generating StartIndex...N
template <unsigned N, unsigned StartIndex>
struct GenerateNumberSubSequence
    : GenerateNumberSequence<N, StartIndex, N>
{
};


// This class is awkward for human use when constructing, but
// once constructed it acts very similar to FixedStringConstant
template <std::size_t N>
class VariableStringConstant
{
public:
    template <typename... Characters>
    constexpr VariableStringConstant( Characters... characters )
        : m_value{ characters..., '\0' },
          m_size( N )
    {
    }

    // Fuck, can only handle equal length strings currently
    //template <typename A, typename B>
    //constexpr VariableStringConstant( const A& a, const B& b, NumberSequence<Numbers...> t )
    //    : m_value{ a[Numbers]..., b[Numbers]..., '\0' },
    //      m_size( N )
    //{
   //}

    constexpr char operator[]( std::size_t n )
    {
        return n < m_size ? m_value[n] : throw std::out_of_range("");
    }

    constexpr const char* const Get( ) { return m_value; }
    constexpr const std::size_t Size( ) { return m_size; }

private:
    const char m_value[N + 1];
    const std::size_t m_size;
};

// Fuck, can only handle equal length strings currently
template <typename A, typename B, class T1, class T2>
constexpr VariableStringConstant<A::Size( ) + B::Size( )> VariableStringConcat( const A& a, const B& b, T1 t1, T2 t2 )
{
    return VariableStringConcatInner( a, b, t1, t2 );
}

template <typename A, typename B, unsigned... NumbersA, unsigned... NumbersB>
constexpr VariableStringConstant<A::Size( ) + B::Size( )> VariableStringConcatInner( const A& a, const B& b, NumberSequence<NumbersA...> t1, NumberSequence<NumbersB...> t2 )
{
    return VariableStringConstant<A::Size( ) + B::Size( )>( a[NumbersA]..., b[NumbersB]... );
}

// This class allows for easy definition of a string constant
// in a more natural and intuitive way
template <std::size_t N>
class FixedStringConstant
{
public:
    constexpr FixedStringConstant( const char(&value)[N + 1] )
        : m_value( value )
    {
    }
    
    constexpr char operator[]( std::size_t n )
    {
        return n < m_size ? m_value[n] : throw std::out_of_range("");
    }

    constexpr const char* const Get( ) { return m_value; }
    constexpr static std::size_t Size( ) { return m_size; }

private:
    const char* const m_value;
    static const std::size_t m_size = N;
};

template <typename A, typename B>
constexpr VariableStringConstant<A::Size( ) + B::Size( )> ConcatStrings( const A& a, const B& b )
{
    // return VariableStringConstant<A::Size( ) + B::Size( )>( 'a', 'b', 'c' );
    //return VariableStringConstant<A::Size( ) + B::Size( )>( a, b, GenerateFullNumberSequence<5>::type( ) );
    return VariableStringConcat( a, b, typename GenerateFullNumberSequence<A::Size( ) - 1>::type( ), typename GenerateFullNumberSequence<B::Size( ) - 1>::type( ) );
}


/*
void print_number( int N )
{
    std::cout << N << std::endl;
}

template <typename T>
void print_stuff() { }

template <unsigned... Numbers>
void print_stuff<NumberSequence<Numbers...> >( )
{
    print_number(Numbers)...;
}
*/

int main()
{
    GenerateFullNumberSequence<5> bob;
    //GenerateNumberSubSequence<9, 4>::type jim = {0, 1, 2, 3, 4, 5};
    
    constexpr FixedStringConstant<3> jim( "hey" );
    constexpr FixedStringConstant<10> you( " you guys!" );
    //constexpr VariableStringConstant<4> guys( 'g', 'u', 'y', 's' );
    
    constexpr std::size_t ta = jim.Size( );
    constexpr auto ja = ConcatStrings( jim, you );
    
    std::cout << ja.Get( ) << std::endl;
}