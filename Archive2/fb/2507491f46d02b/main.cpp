#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
using namespace boost;

// (1) 
template< class F >
typename enable_if<is_void<typename result_of<F(int)>::type>, bool>::type
f (F const& x)
{
  x(1);
  return true;
}

// (2)
template< class F >
typename enable_if<is_void<typename result_of<F(int,int)>::type>, bool>::type
f (F const& x)
{
  x(1,2);
  return true;
}

struct A {
  template <typename> struct result {};
  template <typename F>
  struct result<F(int)>
  {
      typedef void type;
  };
  
  void operator()(int) const { }
};

int main()
{
  A a;
  f (a); // expecting f(F) version (1) to be called here.
}
