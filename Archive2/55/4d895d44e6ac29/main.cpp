#include <type_traits>
#include <utility>

using namespace std;

template <class T> struct propagate_const {
template <class U,
            typename enable_if<!is_convertible<U&&, T>::value &&
                                  is_constructible<T, U&&>::value>::type=true>
  explicit constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }

  template <class U,
            typename enable_if<is_convertible<U&&, T>::value &&
                                  is_constructible<T, U&&>::value>::type=false>
  constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }
  T* t_;
};