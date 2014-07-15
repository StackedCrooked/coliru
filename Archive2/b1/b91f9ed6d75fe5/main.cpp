#ifndef CHECKED_STATIC_CAST_H_
#define CHECKED_STATIC_CAST_H_

#include <limits>

namespace checked_static_cast {
  template<typename T, typename U, bool S>
  struct StaticCast { };

  template<typename T, typename U>
  struct StaticCast<T,U,true> {
    static T f(U a_value)
    {
      if (a_value < std::numeric_limits<T>::min() ||
          a_value > std::numeric_limits<T>::max()) {
        __builtin_trap();
      }

      return static_cast<T>(a_value);
    }
  };

  template<typename T, typename U>
  struct StaticCast<T,U,false> {
    static T f(U a_value) {
      return static_cast<T>(a_value);
    }
  };

  template<typename T, typename U>
  T checked_static_cast(U a_value)
  {
    return StaticCast<T,U, std::numeric_limits<T>::is_specialized>::f(a_value);
  }
}

#define static_cast checked_static_cast::checked_static_cast

#endif // CHECKED_STATIC_CAST_H_

int main() {
    return static_cast<int>(1U);
}