#include <memory>
#include <utility>

struct objectA {};
struct objectB {};

std::pair<objectA*,objectB*> func();
std::tuple<objectA*,objectB*,objectA*> func2();

    template<class...Ts, template<class...>class Tup, class... Us, size_t...Is>
    Tup<Ts...> tuple_cast(std::index_sequence<Is...>,Tup<Us...>&&u){
      return Tup<Ts...>{static_cast<Ts>(std::get<Is>(std::move(u)))...};
    }
    template<class...Ts, template<class...>class Tup, class... Us, size_t...Is>
    Tup<Ts...> tuple_cast(std::index_sequence<Is...>,Tup<Us...>const&u){
      return Tup<Ts...>(static_cast<Ts>(std::get<Is>(u))...);
    }
    template<class...Ts, template<class...>class Tup, class... Us>
    Tup<Ts...> tuple_cast(Tup<Us...>&&u){
      static_assert( sizeof...(Ts)==sizeof...(Us), "must map one type to one type" );
      return tuple_cast<Ts...>(std::index_sequence_for<Us...>{}, std::move(u));
    }
    template<class...Ts, template<class...>class Tup, class... Us>
    Tup<Ts...> tuple_cast(Tup<Us...>const&u){
      static_assert( sizeof...(Ts)==sizeof...(Us), "must map one type to one type" );
      return tuple_cast<Ts...>(std::index_sequence_for<Us...>{}, u);
    }

template<class A>
struct as_unique{using type=A;};
template<class A>
struct as_unique<A*>{using type=std::unique_ptr<A>;};
template<class A>
using as_unique_t=typename as_unique<A>::type;


template<class...Ts, template<class...> class Tuple>
Tuple<as_unique_t<Ts>...> take_ownership(Tuple<Ts...>&& t){
  return tuple_cast<as_unique_t<Ts>...>(std::index_sequence_for<Ts...>{}, std::move(t));
}

int main() {
    auto p = take_ownership(func());
    auto q = take_ownership(func2());
}
