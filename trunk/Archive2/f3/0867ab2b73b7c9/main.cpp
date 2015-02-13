#include <type_traits>

template <bool...> struct bool_pack;
template <bool... B>
using any_true = std::integral_constant<bool,
  !std::is_same<bool_pack<false, B...>, bool_pack<B..., false>>{}>;

template <typename> struct CClassA {};

namespace detail {
  template <template <class...> class, typename>
  struct IsSpec : std::false_type {};
  template <template <class...> class T, typename... U>
  struct IsSpec<T, T<U...>> : std::true_type {};
}

template <typename U, template <class...> class... T>
using IsSpecialization = any_true<detail::IsSpec<T, std::decay_t<U>>{}...>;

// TEST

template <typename T> class CClassA;
template <typename T> class CClassB;

static_assert( IsSpecialization<CClassB<int>, CClassA, CClassB>{}, "" );
static_assert( !IsSpecialization<void, CClassA, CClassB>{}, "" );

int main() {}
