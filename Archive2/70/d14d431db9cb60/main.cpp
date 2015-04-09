#include <tuple>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

template<class T>struct tag{using type=T;};

template<class X>
struct make_very_const:tag<const X> {};
template<class X>
using make_very_const_t=typename make_very_const<X>::type;
// makes code below easier to write (namely, the pointer code):
template<class X>
struct make_very_const<const X>:tag<const make_very_const_t<X>> {};
template<class X>
struct make_very_const<volatile X>:tag<const volatile make_very_const_t<X>> {};
template<class X>
struct make_very_const<const volatile X>:tag<const volatile make_very_const_t<X>> {};
// references:
template<class X>
struct make_very_const<X&>:tag<make_very_const_t<X>&>{};
template<class X>
struct make_very_const<X&&>:tag<make_very_const_t<X>&&>{};
// pointers:
template<class X>
struct make_very_const<X*>:tag<make_very_const_t<X>*const>{};
// std::reference_wrapper:
template<class X>
struct make_very_const<std::reference_wrapper<X>>:tag<std::reference_wrapper<make_very_const_t<X>>const>{};

int main(){
    std::cout << std::is_same<make_very_const_t<int**&>, int const*const*const&>{} << '\n';
}