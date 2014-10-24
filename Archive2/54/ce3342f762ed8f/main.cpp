#ifndef AT_HPP_INCLUDED
#define AT_HPP_INCLUDED

#include "requires.hpp"
#include "size.hpp"

template< typename Type
        , typename EnableIF = has_member(Type,[0])
        >
auto at( Type const& t, std::size_t i )
    -> decltype(i < size(t) ? t[i] : 0)
{
  return i < size(t) ? t[i] : 0;
}

template< int Index
        , typename Type
        , typename EnableIF = has_member(Type,[0])
        >
auto at( Type const& t )
    -> decltype(Index < size(t) ? t[Index] : 0)
{
  return Index < size(t) ? t[Index] : 0;
}

#endif