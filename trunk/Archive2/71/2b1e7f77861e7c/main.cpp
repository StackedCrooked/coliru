
// LineNumber<N>::type is the type defined on the nearest line <= N
template<int N> struct LineNumber;
template<>      struct LineNumber<0> { typedef void type; };
template<int N> struct LineNumber : LineNumber<N - 1> { }; // recursively search upwards

#define REGISTER_TYPE(Type) \
    struct Type { typedef typename LineNumber<__LINE__ - 1>::type previous_type; }; \
    template<> struct LineNumber<__LINE__> { typedef Type type; };



REGISTER_TYPE(Spades)
REGISTER_TYPE(Hearts)


REGISTER_TYPE(Diamonds)

// empty lines are ok

REGISTER_TYPE(Clubs)


#include <type_traits>

static_assert(std::is_same<Spades::previous_type,   void>::value, "");
static_assert(std::is_same<Hearts::previous_type,   Spades>::value, "");
static_assert(std::is_same<Diamonds::previous_type, Hearts>::value, "");
static_assert(std::is_same<Clubs::previous_type,    Diamonds>::value, "");
