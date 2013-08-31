#include <utility>

namespace ns {

template<typename T>
T&& unref(T&& t)
{ return std::forward<T>(t); }
   
template<typename T>
auto id(T&& t)
-> decltype( unref(std::forward<T>(t)) )
{ return unref(std::forward<T>(t)); }

namespace adl {
   
struct ref {};

int* unref(ref const&) { return nullptr; }
   
} // adl

using adl::ref;

} // ns

int main()
{
   struct {}_ = ns::id(ns::ref {});
}