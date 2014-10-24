#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include "at.hpp"
#include "size.hpp"
#include "point2D.hpp"
#include "point3D.hpp"
#include "pointND.hpp"
#include <cmath>

template<typename P1, typename P2>
double distance(P1 const& p1, P2 const& p2)
{
  double r{0};
  auto s = std::max(size(p1),size(p2));

  for(std::size_t i=0;i<s;++i)
  {
    auto d = at(p1,i) - at(p2,i);
    r += d*d;
  }

  return std::sqrt(r);
}

#endif