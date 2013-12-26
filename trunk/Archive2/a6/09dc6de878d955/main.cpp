#include <iostream>
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility> 
#include <boost/variant.hpp>
 
using variant_t = boost::variant<int, float, bool>;

namespace impl {
  struct forward {
    template<typename F, typename... Ts>
    forward (F f, Ts&&... ts) { f (std::forward<Ts> (ts)...); }
  };
};
 
template <typename... Args>
void foo(void (*fptr)(Args...))
{
  std::vector<variant_t> const vars{ { 1 }, { 2.3f }, { false } };

  auto cit = vars.cbegin ();

  using Func = decltype (fptr);
  using Tupl = std::tuple<Func, Args const&...>;

  std::pair<impl::forward, int> (
    std::piecewise_construct, Tupl { fptr, boost::get<Args> (*cit++) ... }, std::tuple<int> { 0 }
  );
}
 
void bar(int i, float f, bool b)
{
  std::cout << i << " " << f << " " << b << std::endl;
}
 

int
main (int argc, char *argv[])
{
  foo (&bar);
}