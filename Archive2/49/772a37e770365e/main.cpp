namespace std
{
    using size_t = unsigned long long;
}

template< std::size_t... Ns >
struct indices
{
  using next = indices< Ns..., sizeof...( Ns ) >;
};

template< std::size_t N >
struct make_indices
{
  using type = typename make_indices< N - 1 >::type::next;
};

template<>
struct make_indices< 0 >
{
  using type = indices<>;
};

constexpr std::size_t length( const char* str )
{
  return *str ? ( length( str + 1 ) + 1 ) : 0;
}

template< template< char... > class C,
          typename T,
          typename = typename make_indices< length( T::str() ) >::type >
struct make_impl;

template< template< char... > class C,
          typename T,
          std::size_t ... Is >
struct make_impl< C, T, indices< Is... > >
{
  using type = C< T::str()[ Is ]... >;
};

template< template< char... > class C, typename T >
using make = typename make_impl< C, T >::type;

template< char... > struct foo {};

int main()
{
    struct hallo { static constexpr const char* str() { return "Hallo"; } };
    make< foo, hallo > m;
    m.f();
}
