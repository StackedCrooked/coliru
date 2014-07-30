#include <type_traits>

template< typename T >
struct function_traits;

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) >
{
  constexpr static const std::size_t arity = sizeof...( Ts );
  using result_type = R;
};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) const > : function_traits< R( Ts... ) > {};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) & > : function_traits< R( Ts... ) > {};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) const & > : function_traits< R( Ts... ) > {};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) && > : function_traits< R( Ts... ) > {};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) const && > : function_traits< R( Ts... ) > {};

template <typename MemFuncType>
class MemberWrapper;

template <typename Ret, typename T>
class MemberWrapper<Ret T::*>
{
  static_assert( function_traits<Ret>::arity <= 4,
                 "More than 4 arguments are not allowed" );
};

struct Test
{
    void f( int, int, double, float, int ) const & {}
};

int main()
{
    MemberWrapper< decltype(&Test::f) >();
}
