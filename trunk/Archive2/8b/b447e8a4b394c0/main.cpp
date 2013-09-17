#include <type_traits>
#include <cstdint>
#include <climits>
#include <tuple>

namespace tambourine { namespace types {

  enum type_sign   { int_signed, int_unsigned, floating_point };
  enum type_layout { fixed, variable_length };

  template<type_layout layout, type_sign sign, size_t bits>
  struct basic_type {

    template<typename...>
    struct find_suitable_type {
      using type = void;
    };

    template<typename T, typename... Ts>
    struct find_suitable_type<T, Ts...> {
      using type = typename std::conditional<
        /* if   */ ((sizeof (T) * CHAR_BIT) < bits),
        /* then */ typename find_suitable_type<Ts...>::type,
        /* else */ T
      >::type;
    };

    using local_type = typename std::tuple_element<sign, std::tuple<
      /* int_signed     */ typename find_suitable_type< int8_t,  int16_t,     int32_t,  int64_t>::type,
      /* int_unsigned   */ typename find_suitable_type<uint8_t, uint16_t,    uint32_t, uint64_t>::type,
      /* floating_point */ typename find_suitable_type<  float,   double, long double          >::type
    >>::type;

    local_type val;
  };

  inline constexpr size_t
  operator"" _bit (unsigned long long val) {
    return val;
  }

  using s8  = basic_type<fixed, int_signed,    8_bit>;
  using u24 = basic_type<fixed, int_unsigned, 24_bit>;
}} /* namespace tambourine::types */

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