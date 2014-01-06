#include <boost/preprocessor/seq.hpp>
#include <type_traits>
#include <utility>

#define IO_DECLVAL(_1, _2, type) std::declval<type>()

#define IO_DECLVALS(types) BOOST_PP_SEQ_TRANSFORM(IO_DECLVAL, ~, types)

#define IO_GENERATE_ABILITY_TRAIT(name, types)                                 \
    template <typename Device, typename = void> struct can_##name : public std::false_type {};  \
                                                                               \
    template <typename Device                                                 \
>                     \
    struct can_##name<Device, decltype(std::declval<Device>().name(                 \
                  BOOST_PP_SEQ_ENUM(IO_DECLVALS(types))))> : public std::true_type {}

namespace io {
    IO_GENERATE_ABILITY_TRAIT(read, (char*)(char*));
    IO_GENERATE_ABILITY_TRAIT(write, (char const*)(char const*));
}

#undef IO_GENERATE_ABILITY_TRAIT
#undef IO_DECLVALS
#undef IO_DECLVAL
