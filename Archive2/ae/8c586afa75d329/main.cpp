#include <iostream>
#include <string>
#include <vector>




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

int main()
{
    GenerateFullNumberSequence<5> bob;
    //GenerateNumberSubSequence<9, 4>::type jim = {0, 1, 2, 3, 4, 5};
    
    //std::cout << jim << std::endl;
}