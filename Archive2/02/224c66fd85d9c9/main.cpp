#include <cassert>
#include <type_traits>
 
#define ENABLE_IF(x) \
  typename std::enable_if<x::value>::type* = nullptr
 
template <typename T>
struct optional
{
  // optional always uninitialized
  explicit operator bool() const { return false; }
  T value() const { throw int(); }
 
  template <typename U, ENABLE_IF(std::is_convertible<U, T>)>
  T value_or(U const& v) const
  {
    if (*this)
      return this->value();
    else
      return v;
  }
 
  template <typename F, ENABLE_IF(!std::is_convertible<F, T>)>
  T value_or(F const& f) const
  {
    if (*this)
      return this->value();
    else
      return f();
  }
};
 
int def()
{
  return -1;
}
 
int main()
{
  optional<int> oi;
  assert (oi.value_or(1) == 1);
  assert (oi.value_or(&def) == -1);
}