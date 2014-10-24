#ifndef COORD_HPP_INCLUDED
#define COORD_HPP_INCLUDED

template<typename Point, int Index = -1>
struct coord;

template<typename Point, int Index = -1>
using coord_t = typename coord<Point,Index>::type;

#endif