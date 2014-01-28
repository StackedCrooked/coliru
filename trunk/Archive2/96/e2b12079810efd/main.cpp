#include <type_traits>
#include <limits>

#include <cstdlib>
#include <cstdint>
#include <cstddef>

using boolean_type = bool;
using size_type = std::size_t;

using near_type = std::int8_t;
using far_type = std::int32_t;

using opcode_type = std::uint8_t;

template< typename T >
boolean_type add_displacement(T const _displacement)
{
    static_assert(std::is_integral< T >::value,
                  "!");
    using U = typename std::make_unsigned< T >::type;
    constexpr size_type const digits_(std::numeric_limits< opcode_type >::digits);
    auto const offset_ = static_cast< U >(_displacement);
    for (size_type i = 0; i < sizeof(U) / sizeof(opcode_type); ++i) {
        /*instance_.code_.push_back(static_cast< opcode_type >(offset_ >> (digits_ * i)));*/
    }
    return true;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
}
#pragma GCC diagnostic pop

boolean_type inderect_address(/*register_type const _base,*/ boolean_type const _increase, size_type const _displacement)
{
    /*...*/
    auto const displacement_ = static_cast< near_type >(_displacement);
    static_assert(std::is_same< decltype(+displacement_), decltype(-displacement_) >::value, "!");
    if (_increase) {
        return add_displacement< near_type >(+displacement_);
    } else {
        return add_displacement< near_type >(-displacement_);
    }
    /*...*/
}

int main()
{
    -std::int8_t{};
    inderect_address(boolean_type{}, size_type{}); 
    return EXIT_SUCCESS;
}

