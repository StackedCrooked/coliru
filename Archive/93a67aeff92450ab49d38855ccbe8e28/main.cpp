#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <functional>
 
template<class F, class T1, class T2>
auto foldl(F f, T1&& v1, T2&& v2)
  -> decltype(f(std::forward<T1>(v1), std::forward<T2>(v2)))
{
  return f(std::forward<T1>(v1), std::forward<T2>(v2));
}
 
template<class F, class T1, class T2, class... Ts>
auto foldl(F f, T1&& v1, T2&& v2, Ts&&... vs)
  -> decltype(f(std::declval<T1>(), std::declval<T2>()))
{
  return foldl(f, f(std::forward<T1>(v1), std::forward<T2>(v2)), std::forward<Ts>(vs)...);
}
 
int main()
{
    auto x = foldl(std::plus<std::string>(), "", "Hello, ", "World.\n", "How ", "are ", "you?\n");
    std::cout << x << "\n";
 
    return 0;
}