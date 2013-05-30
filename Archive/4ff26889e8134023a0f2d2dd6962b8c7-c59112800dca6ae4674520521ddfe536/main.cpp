#include <vector>
#include <list>
#include <cstddef>

template < typename Cont >
auto try_reserve(Cont& p, std::size_t n)
-> decltype( p.reserve(n) )
{
   return p.reserve(n);
}

template < typename Cont >
void try_reserve(Cont& p, std::size_t n, ...)
{}

int main()
{
  std::list<int> a = {1,2,3,4};
  std::vector<int> b = {1,2,3,4};
  
  try_reserve(a, 42);
}
