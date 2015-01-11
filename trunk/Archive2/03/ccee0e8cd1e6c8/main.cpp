#include <iostream>
#include <utility>
#include <string>
#include <tuple>

template <typename>
struct apply_impl;

template <std::size_t... Index>
struct apply_impl<std::index_sequence<Index...>>
{
  template <typename F, typename... T>
  auto operator()(F&& f, std::tuple<T...>& t)
  {
    return std::forward<F>(f)(std::forward<T>(std::get<Index>(t))...);
  }
};

template <typename F, typename... T>
auto apply(F&& f, std::tuple<T...>& t)
{
  return apply_impl<std::index_sequence_for<T...>>()(std::forward<F>(f), t);
}

template <typename F, typename... T>
auto apply(F&& f, T&&... t)
{
  return [f = std::forward<F>(f),
          t = std::forward_as_tuple<T...>(std::forward<T>(t)...)
         ]() mutable { return apply(std::forward<F>(f), t); };
} 
 
struct foo
{
  template <typename T>
  foo(T&&) { std::cout << "rvalue overload\n"; }
    
  template <typename T>
  foo(T&) { std::cout << "lvalue overload\n"; }
};
 
template <typename... T>
void bar(T&&... args)
{
  [&args...]() { foo{args...}; } ();
}

template <typename... T>
void fun(T&&... args)
{
  apply([](auto&&... args) { foo{std::forward<decltype(args)>(args)...}; }, std::forward<decltype(args)>(args)...)();
}

int main()
{   
    bar(1);
    std::string s = "Ala ma kota";
    bar(s);
    
    fun(1);
    fun(s);
}