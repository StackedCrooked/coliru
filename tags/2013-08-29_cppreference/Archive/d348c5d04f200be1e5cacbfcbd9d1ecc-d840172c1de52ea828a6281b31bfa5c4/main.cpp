#include <utility>
#include <type_traits>

namespace aux{
template<class T>
struct any{ template<class U> any(U&&){} };

template<class... Ts>
struct back{
   template<class T>
   static T&& select(any<Ts>..., T&& v){ return std::forward<T>(v); }
};
} // aux::

namespace meta{
template<class T> struct identity{ using type = T; };

template<class T> using Invoke = typename T::type;
template<class T> using Unqualified = Invoke<std::remove_cv<Invoke<std::remove_reference<T>>>>;

template<class T, class... Ts>
struct back{
  using type = Invoke<Unqualified<decltype(aux::back<Ts...>::select(identity<T>{}, identity<Ts>{}...))>>;
};

template<class... Ts>
using Back = Invoke<back<Ts...>>;
} // meta::

template<class T, class... Ts>
auto back(T&& v, Ts&&... vs)
  //-> decltype(aux::back<Ts...>::select(std::declval<T>(), std::declval<Ts>()...))
  -> meta::Back<T, Ts...>&&
{
    return aux::back<Ts...>::select(std::forward<T>(v), std::forward<Ts>(vs)...);
}

static_assert(std::is_same<int&&, decltype(back(3.14f, 13.37, true, 'x', "hi", 42))>(), "fix it, idiot");

int main(){}