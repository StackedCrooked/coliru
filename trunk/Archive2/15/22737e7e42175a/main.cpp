#include <tuple>

namespace detail {
  using namespace std;

  template<class... Ts> 
  struct magic_impl {
    template<class T>
    struct hack {
      typedef T type;

      template<class U = int> hack (U&& = {}) { } 

      operator type () { return {}; }
    };  

    template<class... Us> 
    operator tuple<Us...> () const && {
      return [this] (hack<Ts>..., auto... xs) {
        return tuple_cat<tuple<Ts const&...>, tuple<decltype(xs)...>> (src, {});
      } ( hack<Us> {}... );
    }   

    tuple<Ts...> const& src;
  };  
}

template<class... Ts> 
detail::magic_impl<Ts...>
make_expandable (std::tuple<Ts...> const& src) {
  return { src };
}

#include <iostream>

int main () {
  std::tuple<int,int>          x { 1, 2 };
  std::tuple<float,float,bool> y = make_expandable (x);

  std::cout << std::get<0> (y) << " " << std::get<1> (y) << " " << std::get<2> (y);
}