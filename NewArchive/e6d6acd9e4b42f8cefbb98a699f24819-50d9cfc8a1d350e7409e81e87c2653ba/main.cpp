#include <utility>

namespace foo {
    
template<typename T>
T&& unref(T&& t)
{ return std::forward<T>(t); }
    
} // foo

namespace adl {
    
namespace tricks {
    
using foo::unref;
    
template<typename T>
auto adl_unref(T&& t) -> decltype( unref(std::forward<T>(t)) )
{ return unref(std::forward<T>(t)); }

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

namespace ref_adl {
   
struct ref {};

int* unref(ref const&) { return nullptr; }
   
} // ref_adl

using ref_adl::ref;

} // ns

int main()
{
   struct {}_ = ns::id(ns::ref {});
}