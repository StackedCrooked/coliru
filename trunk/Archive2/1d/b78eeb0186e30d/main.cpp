
#include <iostream>
#include <utility>

struct Functor2 {
  int operator()(int id) const &
  {
    std::cout << "Functor2 &... " << id << std::endl;
    return id;
  }
  int operator()(int id) &&
  {
    std::cout << "Functor2 &&... " << id << std::endl;
    return id;
  }
};

struct Functor1 {
  int operator()(int id) const
  {
    std::cout << "Functor1 ... " << id << std::endl;
    return id;
  }
};

template<class F, class... Args>
auto apply_impl(F&& func, Args&&... args) -> decltype(std::forward<F>(func)(std::forward<Args>(args)...)) {
  return std::forward<F>(func)(std::forward<Args>(args)...);
}

template<class F, class... Args>
auto apply_impl_2(F&& func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
  return func(std::forward<Args>(args)...);
}

int main()
{
  Functor1 func1;
  apply_impl_2(func1, 1);
  apply_impl_2(Functor1(), 2);
  apply_impl(func1, 3);
  apply_impl(Functor1(), 4);

  Functor2 func2;
  apply_impl_2(func2, 5);
  apply_impl_2(Functor2(), 6);
  apply_impl(func2, 7);
  apply_impl(Functor2(), 8);
}
