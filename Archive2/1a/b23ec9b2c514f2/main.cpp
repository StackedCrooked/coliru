#include <type_traits>

template <typename X, typename Y>
struct I
{
    I(X*, Y){}
};

struct T
{
  int& fn(int) { static int i; return i; }
};

template <typename C>
using IT = I<C, typename std::remove_reference<decltype(std::declval<C&>().fn(0))>::type>;

template <typename C>
IT<C> fn(C& c)
{
  return IT<C>(&c, c.fn(1));
}

#include <iostream>
int main()
{
    T t;
    fn(t);
    std::cout << "DONE"<<std::endl;   
}
