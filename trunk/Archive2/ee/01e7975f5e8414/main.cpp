#include <iostream>
#include <tuple>
#include <utility>
   
template<typename T>
T default_init()
{
   return T();
}

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template<typename... Args, int... indices>
void print_tuple(const std::tuple<Args...>& tuple, seq<indices...>)
{
   using swallow = int[];
   (void)swallow{0, (void(std::cout << std::get<indices>(tuple) << std::endl), 0)...};
}

template<typename... Args>
void print_tuple(const std::tuple<Args...>& tuple)
{
   print_tuple(tuple, typename gens<sizeof...(Args)>::type{});
}

template<typename... Args>
void print()
{
   std::cout << std::endl;
}

template<typename T, typename... Args>
void print(const T& t, const Args&... args)
{
   std::cout << t << " ";
   print(args...);
}

template<typename... Args>
void f(const Args&... args)
{
   print(args...);
}

template<typename... Args, int... indices>
void forward_tuple(const std::tuple<Args...>& tuple, seq<indices...>)
{
   f(std::get<indices>(tuple)...);
}

template<typename... Args>
void f()
{
   std::tuple<Args...> tuple{};
   forward_tuple(tuple, typename gens<sizeof...(Args)>::type{});
}

int main()
{
   f<int, float, double>();
   f(1, 1.0F, 1.5);
}
