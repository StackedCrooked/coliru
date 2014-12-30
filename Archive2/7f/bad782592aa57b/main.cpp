#include <type_traits>

template <typename X, typename Y>
struct I
{};

struct T
{
  int& fn(int);
};

template <typename C>
using IT = I<typename std::remove_reference<decltype(std::declval<C&>().fn(0))>::type, C>;

template <typename C>
IT<C> fn(C& c)
{
  return IT<C>();
}

int main()
{
    
}
