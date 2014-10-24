#ifndef SIZE_HPP_INCLUDED
#define SIZE_HPP_INCLUDED

#include "requires.hpp"

template<typename T, std::size_t N>
std::size_t size( const T(&x)[N] )
{
  return N;
}

template< typename Type
        , typename EnableIF = has_member(Type,.size())
        >
std::size_t size( Type const& t )
{
  return t.size();
}

#endif