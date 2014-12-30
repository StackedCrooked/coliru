#include <string>
#include <type_traits>
#include <iostream>
#include <vector>

#include <boost/lexical_cast.hpp>

template <typename T, typename=void>
struct IsLexCastable : std::false_type {};

template <typename T>
struct IsLexCastable<T,
            decltype(void(std::declval<std::ostream&>() << std::declval<T>()))>
  : std::true_type {};

static_assert( !IsLexCastable<std::vector<int>>{}, "" );
  
int main()
{
}