#include <type_traits>
#include <cstdint>
#include <climits>
#include <tuple>

namespace tambourine { namespace types {

  enum type_sign   { int_signed, int_unsigned, floating_point };
  enum type_layout { fixed, variable_length };

  template<type_layout layout, type_sign sign, size_t bits>
  struct basic_type {
    using local_representation_types = typename std::tuple_element<sign, std::tuple<
      /* int_signed     */ std::tuple< int8_t,  int16_t,     int32_t,  int64_t>,
      /* int_unsigned   */ std::tuple<uint8_t, uint16_t,    uint32_t, uint64_t>,
      /* floating_point */ std::tuple<  float,   double, long double>
    >>::type;

    template<typename...>
    struct suitable_local_representation {
      using type = void;
    };

    template<typename T, typename... Ts>
    struct suitable_local_representation<T, Ts...> {
      using type = typename std::conditional<
        /* if   */ ((sizeof (T) * CHAR_BIT) < bits),
        /* then */ typename suitable_local_representation<Ts...>::type,
        /* else */ T
      >::type;
    };

    template<typename... Ts> static
    typename suitable_local_representation<Ts...>::type
    find_suitable_representation_type (std::tuple<Ts...> const&);

    using local_type = decltype (
      find_suitable_representation_type (
        std::declval<local_representation_types> ()
      )
    );

    local_type val;
  };

  inline constexpr size_t
  operator"" _bit (unsigned long long val) {
    return val;
  }

  using s8  = basic_type<fixed, int_signed,    8_bit>;
  using u24 = basic_type<fixed, int_unsigned, 24_bit>;
}} /* namespace tambourine::types */

/* ....................... */

#include <type_traits>
#include <cstdint>

int
main (int argc, char *argv[])
{
  using namespace tambourine::types;

  static_assert (
    std::is_same<s8::local_type, int8_t>::value,
    "s8 != int8_t"
  );

  static_assert (
    std::is_same<u24::local_type, uint32_t>::value,
    "u24 != uint32_t"
  );
}