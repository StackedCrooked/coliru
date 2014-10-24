#ifndef POINT3D_HPP_INCLUDED
#define POINT3D_HPP_INCLUDED

#include <array>
#include "coord.hpp"

template<typename Type>
using point3D = std::array<Type,3>;

template<typename Type, int Index>
struct coord<point3D<Type>,Index>
{
  using type = Type;
};

#endif
