#include <tuple>
#include <type_traits>

namespace detail {
  using namespace std;

  template<class T>
  struct magic {
    using value_type     = decay_t<T>;
    using reference_type = T&&;

    reference_type src;

    template<size_t N, class Target>
    auto value_or_t (reference_type x, ...) {
      return std::get<N> (forward<reference_type> (x));
    }

    template<
      size_t N,
      class Target,
      class Ret = tuple_element_t<N, Target>,
      class     = enable_if_t<(N >= tuple_size<value_type> {})>
    >
    auto value_or_t (reference_type, int) -> Ret {
      return {};
    }

    template<class Target, size_t... Ns>
    auto worker (index_sequence<Ns...>) {
      return Target { value_or_t<Ns, Target> (forward<reference_type> (src), 0)... };
    }

    template<class Tuple, class index_seq = make_index_sequence<tuple_size<Tuple> {}>>
    operator Tuple () {
      return worker<Tuple> (index_seq {});
    }
  };
}

template<class T>
detail::magic<T&&>
make_expandable (T&& src) {
  return { std::forward<T> (src) };
}

// -----------------------------------------------------------

#include <iostream>
#include <memory>
#include <tuple>

int main () {
  {
    std::tuple<int,int>          x { 1, 2 };
    std::tuple<float,float,bool> y = make_expandable (x);

    std::cout << std::get<0> (y) << " " << std::get<1> (y) << " " << std::get<2> (y) << std::endl;
  }
  
  {
    std::tuple<std::unique_ptr<int>>      a { std::make_unique<int> (123) };
    std::tuple<std::unique_ptr<int>, int> b = make_expandable (std::move (a));

    std::cout << *std::get<0> (b) << std::endl;
  } 
}