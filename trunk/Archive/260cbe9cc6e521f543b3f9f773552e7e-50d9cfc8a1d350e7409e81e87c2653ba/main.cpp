#include <utility>

namespace adl {
    
namespace tricks {
    
template<typename T>
auto adl_unref(T&& t) -> decltype( unref(std::forward<T>(t)) )
{ return unref(std::forward<T>(t)); }
    
template<typename T, typename... Ignored>
T&& adl_unref(T&& t, Ignored const&...)
{ return std::forward<T>(t); }

} // tricks

template<typename T>
auto unref(T&& t) -> decltype(tricks::adl_unref(std::forward<T>(t)))
{ return tricks::adl_unref(std::forward<T>(t)); }
    
} // adl

namespace ns {
   
template<typename T>
auto id(T&& t)
-> decltype( adl::unref(std::forward<T>(t)) )
{ return adl::unref(std::forward<T>(t)); }

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