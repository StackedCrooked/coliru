#include <iostream>
#include <type_traits>
#include <mpl>

template<class T>
struct add_ref : mpl::eval_if<
  boost::is_reference<T>,
  mpl::identity<T>,
  mpl::add_reference<T>> {};
  

void main()
{
    return 0;
}
