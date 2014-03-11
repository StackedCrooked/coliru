#include <iostream>
#include <utility>

template<typename T0, typename... Ts>
struct comma_collapse { typedef T0 type; };
template<typename T0, typename T1, typename... Ts>
struct comma_collapse<T0, T1, Ts...> {
    typedef decltype( std::declval<T0>(), std::declval<typename comma_collapse<T1, Ts...>::type>() ) type;
};

template<typename LHS>
LHS&& comma_splice(LHS&& lhs){ return std::forward<LHS>(lhs); }

template<typename LHS, typename RHS, typename... Tail>
typename comma_collapse<LHS,RHS,Tail...>::type&& comma_splice( LHS&& lhs, RHS&& rhs, Tail&&... tail )
{
  auto&& first_two = (std::forward<LHS>(lhs),std::forward<RHS>(rhs));
  return comma_splice(
    std::forward<decltype(first_two)>(first_two),
    std::forward<Tail>(tail)...
  );
}

int main() {
    std::cout << comma_splice( 1, 2, 3, 4, 5, 6 ) << "\n";
	// your code goes here
	return 0;
}