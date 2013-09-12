#include <type_traits>


template< int value> 
constexpr bool check( int i, std::false_type ) noexcept
{
    return value == i;  // void(i) to silence warning (unused param)
}

template< int value, int ... values> 
constexpr bool check( int i, std::true_type = {} ) noexcept
{
  using recurse = std::integral_constant<bool, 1 < sizeof...(values)>;
  return value == i || check<values...>(i, recurse{});
}


int main()
{
    int i = 42;
    bool x = check<1,2,3,41,42,43>(i);
    static_assert( check<1,2,3,41,42,43>(42), "!" );
    static_assert( check<1,2,3,41,42,43>(999), "!" );
}
