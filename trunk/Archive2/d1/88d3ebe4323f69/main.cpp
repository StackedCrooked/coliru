#ifndef BIZARRO_POINT_HPP_INCLUDED
#define BIZARRO_POINT_HPP_INCLUDED

#include <tuple>
#include "at.hpp"
#include "int.hpp"
#include "size.hpp"
#include "coord.hpp"

using bizarro_point = std::tuple<int,double,char>;

template<> struct coord<bizarro_point,-1>
{
  using type = double;
};

template<typename T, int N>
using is_valid = bool_<(N>=0 && N<std::tuple_size<T>::value)>;

namespace details
{
  template<typename T,int N,bool B> struct coord;

  template<typename T, int N> struct coord<T,N,true>
  {
    using type = typename std::tuple_element<N,T>::type;
  };

  template<typename T, int N>
  struct coord<T,N,false> : ::coord<T,-1>
  {};
}

template<int N>
struct coord<bizarro_point,N>
      : details::coord<bizarro_point,N,is_valid<bizarro_point,N>::value>
{
  static_assert(N >= 0, "Invalid dimension index");
};

std::size_t size(bizarro_point const&) { return 3; }

coord_t<bizarro_point>
at(bizarro_point const& p, std::size_t i)
{
  return i==0 ? std::get<0>(p)
              : (i==1 ? std::get<1>(p)
                      : (i==2 ? std::get<2>(p) : 0)
                );
}

template<int N>
coord_t<bizarro_point,N> at ( bizarro_point const& t
                            , int_<N> const&
                            , true_ const&
                            )
{
  return std::get<N>(t);
}

template<int N>
coord_t<bizarro_point,N> at ( bizarro_point const& t
                            , int_<N> const&
                            , false_ const&
                            )
{
  return coord_t<bizarro_point,N>{};
}

template<int N>
coord_t<bizarro_point,N> at( bizarro_point const& t )
{
  return at(t,int_<N>{},is_valid<bizarro_point,N>{});
}

#endif