#ifndef INT_HPP_INCLUDED
#define INT_HPP_INCLUDED

template<int N>
using int_ = std::integral_constant<int,N>;

template<bool N>
using bool_ = std::integral_constant<bool,N>;

using true_  = bool_<true>;
using false_ = bool_<false>;

#endif