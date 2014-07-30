#include <type_traits>

template< typename T >
class function_traits
{
  static_assert( sizeof( T ) == 0,
                 "function_traits<T>: T is not a function type" );
};

template< typename R, typename... Ts >
struct function_traits< R( Ts... ) >
{
  constexpr static const std::size_t arity = sizeof...( Ts );
  using result_type = R;
};

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
    void f( int, int, double, float, int ) {}
};

int main()
{
    MemberWrapper< decltype(&Test::f) >();
}
