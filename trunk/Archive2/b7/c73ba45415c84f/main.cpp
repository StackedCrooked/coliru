#ifndef REQUIRES_HPP_INCLUDED
#define REQUIRES_HPP_INCLUDED

template<typename... Args>
struct void_t
{
  typedef void type;
};

template<typename... Args>
using requires = typename void_t<Args...>::type;

#define has_member(T,Member) decltype(std::declval<T>() Member)
#define has_type(T,Member)   decltype(T::Member)

#endif
