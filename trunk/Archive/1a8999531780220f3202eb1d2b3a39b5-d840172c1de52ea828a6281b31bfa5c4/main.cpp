#include <utility>
#include <type_traits>

namespace aux{
template<class T>
struct any{ template<class U> any(U&&){} };

template<class T> struct identity{ using type = T; };
template<class T> using Identity = typename identity<T>::type;

template<class... Ts, class T>
T&& back(any<Identity<Ts>>..., T&& v){ return std::forward<T>(v); }
} // aux::

template<class T, class... Ts>
auto back(T&& v, Ts&&... vs)
  -> decltype(aux::back<Ts...>(std::declval<T>(), std::declval<Ts>()...))
{
    return aux::back<Ts...>(std::forward<T>(v), std::forward<Ts>(vs)...);
}

static_assert(std::is_same<int&&, decltype(back(3.14f, 13.37, true, 'x', "hi", 42))>(), "fix it, idiot");


int main(){}