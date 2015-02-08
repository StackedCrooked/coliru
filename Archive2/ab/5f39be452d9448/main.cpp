#include <utility>
#include <cstddef>

namespace meta {
  struct ignore final {
    template <typename... Ts>
    constexpr ignore(Ts&&...) noexcept {}
  };

  template <typename>
  using eat = ignore;

  template <std::size_t>
  using eat_n = ignore;
}

namespace fused {
  template <typename Tp, typename... Us>
  constexpr decltype(auto) front(Tp&& t, Us&&...) noexcept {
    return std::forward<Tp>(t);
  }

  template <typename Tp, typename... Us>
  constexpr decltype(auto) back(Tp&& t, Us&&... us) noexcept {
    return [](meta::eat<Us>..., auto&& x) -> decltype(x) {
      return std::forward<decltype(x)>(x);
    }(std::forward<Tp>(t), std::forward<Us>(us)...);
  }

  namespace detail {
    template <std::size_t N, typename = std::make_index_sequence<N>>
    struct at;

    template <std::size_t N, std::size_t... skip>
    struct at<N, std::index_sequence<skip...>> {
      template <typename Tp, typename... Us>
      constexpr decltype(auto) operator()(meta::eat_n<skip>..., Tp&& x,
                                          Us&&...) const noexcept {
        return std::forward<Tp>(x);
      }
    };
  }

  template <std::size_t N, typename... Ts>
  decltype(auto) nth(Ts&&... args) {
    return detail::at<N>{}(std::forward<Ts>(args)...);
  }
}

#include <cassert>
#include <memory>
int main() {
  // test
  {
    // bind rvalue
    auto x = fused::front(unsigned{1u}, 2.0, std::make_unique<char>('3'));
    assert(x == 1u);

    // bind lvalue
    unsigned a = 4u;
    auto const& y = fused::front(a, 2.0, std::make_unique<char>('3'));
    assert(y == 4u);
    assert(&a == &y);
  }
  {
    auto a = 1u;
    auto b = 2.0;
    auto c = fused::back(1u, 2.0, '3');
    assert(c == '3');

    auto const& x = fused::back(a, b, c);
    assert(x == '3');
    assert(&c == &x);

    auto y = fused::back(a, b, std::make_unique<char>('4'));
    assert(y != nullptr);
    assert(*y == '4');
  }
  {
    auto a = 1u;
    auto b = 2.0;
    auto c = '3';

    auto const& x = fused::nth<0>(a, b, c);
    auto const& y = fused::nth<1>(a, b, c);
    auto const& z = fused::nth<2>(a, b, c);

    assert(&a == &x);
    assert(&b == &y);
    assert(&c == &z);

    fused::nth<0>(a, b, c) = 7u;
    assert(a == 7u);
  }
  return 0;
}
