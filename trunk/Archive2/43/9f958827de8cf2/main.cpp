#include <iostream>
#include <tuple>
#include <string>
using namespace std;
 
 
// basically C++14's integer sequence
template<int ...>
struct seq { };
 
template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> { };
 
template<int ...S>
struct gens<0, S...> {
typedef seq<S...> type;
};
 
template<typename Func, typename ...B, int ...S> auto
map_1(Func&& f, std::tuple<B...> &&t, seq<S...>)
-> decltype(std::make_tuple(f(std::get<S>(t))...))
{
return std::make_tuple(f(std::get<S>(t))...);
}
 
template<typename Func, typename ...B> auto
map(Func&& f, std::tuple<B...> &&t)
-> decltype(map_1(std::forward<Func>(f), std::forward<std::tuple<B...>>(t), typename gens<sizeof...(B)>::type()))
{
return map_1(std::forward<Func>(f), std::forward<std::tuple<B...>>(t), typename gens<sizeof...(B)>::type());
}
 
 
// Some functions
double f(double x) { return x; }
size_t f(std::string s) { return s.size(); }
 
template<typename T>
void printFoo(const T& )
{
   std::cout << __PRETTY_FUNCTION__ << std::endl;   
}
 
#define BINDOVERLOADED(X) [](auto&& t) { return X(std::forward<decltype(t)>(t)); }
int main() {
 
auto x = map(BINDOVERLOADED(f), make_tuple(3.14, "a string"));
printFoo(x);
return 0;
}