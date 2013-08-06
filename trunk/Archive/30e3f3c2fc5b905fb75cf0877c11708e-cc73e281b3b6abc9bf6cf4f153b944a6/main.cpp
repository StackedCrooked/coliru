#include <vector>

namespace A {
    struct B {};
    void swap(B&,B&){}
}
 
template<class T>
using swap_func_type = void (*)(T &, T &);
 
template<class T>
swap_func_type<T> get_swap()
{
    using std::swap;
    return swap_func_type<T>(swap);      // Like this
}
 
int main()
{ 
  auto swap_func0 = get_swap<A::B>(); //works, finds A::swap
  auto swap_func1 = get_swap<std::vector>(); //fails, can't find std::swap<std::vector>
}