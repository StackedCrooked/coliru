#ifndef POINT2D_HPP_INCLUDED
#define POINT2D_HPP_INCLUDED

#include <array>
#include "coord.hpp"

template<typename Type>
using point2D = std::array<Type,2>;

template<typename Type, int Index>
struct coord<point2D<Type>,Index>
{
  using type = Type;
};

#endif
