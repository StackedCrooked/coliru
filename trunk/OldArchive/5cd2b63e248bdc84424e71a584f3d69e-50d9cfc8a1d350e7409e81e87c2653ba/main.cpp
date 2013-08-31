#include <iostream>
#include <functional>

template<class Signature>
struct recursive
{
    std::function<std::function<Signature>(recursive)> f;
};

template<class R, class... Args>
using type = std::function<R(Args...)>;

template<class R, class... Args>
using f_type = std::function<type<R, Args...>(type<R, Args...>)>;

template<class R, class... Args>
type<R, Args...> helper_for(f_type<R, Args...> f)
{
   recursive<R(Args...)> r = { [f](recursive<R(Args...)> rf)
   {
      return f([rf](Args... args){ return rf.f(rf)(args...); });
   }};
   return r.f(r);
}

std::function<long(long)> fuck(std::function<long(long)> f)
{
   return [f](long n)->long { return (n <= 1) ? 1 : n * f(n - 1); };
}

int main()
{
   auto fuck_of_fuck = helper_for(f_type<long, long>(fuck));

   std::cout << fuck_of_fuck(10);
}