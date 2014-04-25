#include <utility>
#include <type_traits>

namespace detail
{
  // C++14's std::integer_sequence et.al. as per N3658 / N3797

  template< typename T, T... I >
  struct integer_sequence
  {
    static_assert( std::is_integral< T >::value, "T is not an integral type" );

    using value_type = T;

    static constexpr std::size_t size() noexcept
    {
      return sizeof...( I );
    }
  };

  template< std::size_t... I >
  using index_sequence = integer_sequence< std::size_t, I... >;

  namespace make_integer_sequence_impl
  {
    template< typename T, typename, std::size_t = T::size() >
    struct helper;

    template< typename T, T... Ns, T... Ms, std::size_t S >
    struct helper< integer_sequence< T, Ns... >, integer_sequence< T, Ms... >, S >
    {
      using type = integer_sequence< T, Ns..., ( S + Ns )..., ( 2 * S + Ms )... >;
    };

    template< typename T, T N, typename = void >
    struct make
    {
      static_assert( N >= 0, "N is not a positive value" );

      using type = typename helper< typename make< T, N / 2 >::type, typename make< T, N % 2 >::type >::type;
    };

    template< typename T, T N >
    struct make< T, N, typename std::enable_if< N == 1 >::type >
    {
      using type = integer_sequence< T, 0 >;
    };

    template< typename T, T N >
    struct make< T, N, typename std::enable_if< N == 0 >::type >
    {
      using type = integer_sequence< T >;
    };
  }

  template< typename T, T N >
  using make_integer_sequence = typename make_integer_sequence_impl::make< T, N >::type;

  template< std::size_t N >
  using make_index_sequence = make_integer_sequence< std::size_t, N >;

  template< typename... T >
  using index_sequence_for = make_index_sequence< sizeof...( T ) >;

// end of std::index_sequence

    template<typename Int, typename, Int S>
    struct increasing_integer_range;

    template<typename Int, Int... N, Int S>
    struct increasing_integer_range<Int, integer_sequence<Int, N...>, S>
        : integer_sequence<Int, N+S...>
    {};

    template<typename Int, typename, Int S>
    struct decreasing_integer_range;

    template<typename Int, Int... N, Int S>
    struct decreasing_integer_range<Int, integer_sequence<Int, N...>, S>
        : integer_sequence<Int, S-N...>
    {};
}

template<typename Int, Int S, Int E,  bool Increasing=(S<E)>
struct integer_range;

template<typename Int, Int S, Int E>
struct integer_range<Int, S, E, true>:
    detail::increasing_integer_range<Int, detail::make_integer_sequence<Int, E-S>, S>
{};

template<typename Int, Int S, Int E>
struct integer_range<Int, S, E, false>:
    detail::decreasing_integer_range<Int, detail::make_integer_sequence<Int, S-E>, S>
{};

template<std::size_t S, std::size_t E>
using index_range = integer_range<std::size_t, S, E>;

template<std::size_t... N> void dummy( const detail::integer_sequence< std::size_t, N... >& );

int main()
{
    dummy( index_range< 2, 5 >() );
    dummy( index_range< 5, 2 >() );
}
