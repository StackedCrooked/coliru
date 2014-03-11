#include <iostream>
#include <limits>

template<typename LHS, typename RHS>
constexpr bool greater_than(LHS lhs, RHS rhs)
{ return lhs > rhs; }

int main()
{
    static_assert(greater_than(1, 0), "Oops");
//    static_assert(greater_than(1, 4), "Oops"); // this fails
}
