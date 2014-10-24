#ifndef POINTND_HPP_INCLUDED
#define POINTND_HPP_INCLUDED

#include <vector>
#include "coord.hpp"

template<typename Type>
using pointND = std::vector<Type>;

template<typename Type, int Index>
struct coord<pointND<Type>,Index>
{
  using type = Type;
};

#endif