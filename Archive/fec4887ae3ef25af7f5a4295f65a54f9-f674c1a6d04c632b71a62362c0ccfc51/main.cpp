#include <cstdint>
#include <limits>
#include <type_traits>

template<int MINIMUM, int MAXIMUM>
struct RangeBasedInt
{
    static_assert(MINIMUM <= MAXIMUM, "MINIMUM NEEDS TO BE SMALLER THAN MAXIMUM");
    
    typedef std::conditional<
        // Condition
        (MINIMUM >= 0),
        // If minimum is positive, use decltype
        decltype(MAXIMUM),
        // If minimum is negative, use template magic
        typename std::conditional<
            // Condition
            (std::numeric_limits<decltype(MINIMUM)>::max() >= MAXIMUM),
            // If the decltype can hold our maximum, we're done
            decltype(MINIMUM),
            // If the decltype cannot hold our maximum
            decltype(MAXIMUM)
            >::type
        > std_conditional_type;
    
    typedef typename std_conditional_type::type type;
};

#include <typeinfo>

int main()
{
    static_assert(std::is_same<RangeBasedInt<0,0xFFFF>::type, int>::value, "INVALID TYPE");
}

static_assert(std::is_same<decltype(0x0),int>::value, "SHOULD FAIL DUE TO 2.14.2 [lex.icon]");