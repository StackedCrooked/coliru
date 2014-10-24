#include <functional>

template <typename R>
struct overload;

template <typename R, typename... A>
struct overload<R(A...)>
{
  typedef std::function<R(A...)> F;
  F f_;
  overload(F f): f_(f) {}
  R operator()(A... a)
  {
    return f_(a...);
  }
};

template <typename... T>
struct overloaded_function;

template <>
struct overloaded_function<> {};

template <typename T>
struct overloaded_function<T> : overload<T> {
    overloaded_function(T t): overload<T>(t) {}
    using overload<T>::operator();
};


template <typename T, typename... Ts>
struct overloaded_function<T, Ts...> : overload<T>, overloaded_function<Ts...> {
  overloaded_function(T t, Ts... ts): overload<T>(t), overloaded_function<Ts...>(ts...) {}
  
  using overload<T>::operator();
  using overloaded_function<Ts...>::operator();
};

int main()
{
  overloaded_function<void(float), void(int, int)> f([](float){}, [](int, int){});
  f(1.F);  // build error
  f(2, 3); // build error
  return 0;
}