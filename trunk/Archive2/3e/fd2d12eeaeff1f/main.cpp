#include <type_traits>

template <typename X, typename Y>
struct I
{
    I(X*, Y*){}
};

struct T
{
  int& fn(int);
};

template <typename C>
using IT = I<typename std::remove_reference<decltype(std::declval<C&>().fn(0))>::type, C>;

template <typename C>
IT<C> fn(C& c)
{
  return IT<C>(&c, c.fn());
}

#include <iostream>
int main()
{
    T t;
    fn(t);
    std::cout << "DONE"<<std::endl;   
}
