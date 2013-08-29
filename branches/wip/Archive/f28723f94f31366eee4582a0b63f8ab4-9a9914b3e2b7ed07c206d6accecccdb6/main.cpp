
#include <utility>
#include <tuple>
#include <type_traits>

template<class F, class Acc, class T>
auto variadic_fold(F&& f, Acc&& acc, T&& v)
 -> decltype(f(std::forward<Acc>(acc), std::forward<T>(v)))
{
  return f(std::forward<Acc>(acc), std::forward<T>(v));
}

template<class F, class Acc, class Head, class... Ts>
auto variadic_fold(F&& f, Acc&& acc, Head&& head, Ts&&... vs)
  -> decltype(variadic_fold(f, f(std::forward<Acc>(acc), std::forward<Head>(head)), std::forward<Ts>(vs)...))
{
  return variadic_fold(f, f(std::forward<Acc>(acc), std::forward<Head>(head)), std::forward<Ts>(vs)...);
}

template<unsigned...> struct seq{};
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class F, class Acc, class Tuple, unsigned... Is>
auto tuple_fold(F&& f, Acc&& acc, Tuple&& tuple, seq<Is...>)
  -> decltype(variadic_fold(f, std::forward<Acc>(acc), std::get<Is>(std::forward<Tuple>(tuple))...))
{
  return variadic_fold(f, std::forward<Acc>(acc), std::get<Is>(std::forward<Tuple>(tuple))...);
}

template<class T>
using Invoke = typename T::type;

template<class T>
using Unqualified = Invoke<std::remove_cv<Invoke<std::remove_reference<T>>>>;

template<class F, class Acc, class Tuple, class Size = std::tuple_size<Unqualified<Tuple>>>
auto tuple_fold(F&& f, Acc&& acc, Tuple&& tuple)
  -> decltype(tuple_fold(f, std::forward<Acc>(acc), std::forward<Tuple>(tuple), gen_seq<Size::value>{}))
{
  return tuple_fold(f, std::forward<Acc>(acc), std::forward<Tuple>(tuple), gen_seq<Size::value>{});
}

#include <iostream>

struct print{
    template<class T>
    std::ostream& operator()(std::ostream& os, T&& v) const{
        return os << v << "\n";
    }
};

int main(){
    auto t = std::make_tuple(42, 13.37, true, "hello, world!");
    std::cout << std::boolalpha;
    tuple_fold(print(), std::cout, t);
}