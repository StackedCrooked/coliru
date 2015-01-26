//#define PROBLEM_FIX1
//#define PROBLEM_FIX2

#include <utility>
template<typename Tp>
struct move_capture {
 
  template <typename Up>
  move_capture(Up&&) {}
  move_capture(move_capture const& o)
#if !defined(PROBLEM_FIX1)
   {} // this is noc linking in clang++
#else
  = default; // fix 1: use default
#endif

};

template <typename... Ts>
decltype(auto) make_storage(Ts&&... ts) {
  return [](const move_capture<Ts>... mvs) {
    return [mvs...](auto) {
    };
  }(std::forward<Ts>(ts)...);
}

#include <iostream>
int main() 
{
  std::cout << __VERSION__ << std::endl;
  auto s = make_storage(1);
  (void)s;
#if defined(PROBLEM_FIX2) // fix 2: explicitly use this copy-constructor so that compiler will not remove it
  const move_capture<int> m1(3);
  move_capture<int> m2(m1);
  (void)m2;
#endif
  return 0;
}

// fix 3: switch to g++ 
