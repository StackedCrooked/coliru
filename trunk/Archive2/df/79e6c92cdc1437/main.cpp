#ifndef PIXEL_HPP_INCLUDED
#define PIXEL_HPP_INCLUDED

#include "at.hpp"
#include "size.hpp"
#include "coord.hpp"

struct pixel
{
  int x,y;
};

std::size_t size(pixel const&) { return 2; }

int at(pixel const& p, std::size_t i)
{
  return i==0 ? p.x : (i==1 ? p.y : 0);
}

template<int Index>
struct coord<pixel,Index>
{
  using type = int;
};

#endif