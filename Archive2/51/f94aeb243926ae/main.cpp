#include <functional>

template <typename R, typename... A>
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
  
  friend R do_overload(overload& o, A... a)
  {
      return o(a...);
  }
};

template <typename... T>
struct overloaded_function : public overload<T>...
{
  overloaded_function(T... t): overload<T>(t)... {}
  template<typename... A>
  auto operator()(A... a) -> decltype( do_overload(*this, a...) )
  {
      return do_overload(*this, a...);
  }
};

int main()
{
  overloaded_function<void(float), void(int, int)> f([](float){}, [](int, int){});
  f(1.F);  // build error
  f(2, 3); // build error
  return 0;
}