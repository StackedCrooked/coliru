#pragma once

#include <type_traits>
#include <limits>
#include <utility>

#include <cstdlib>

namespace insituc
{

template< typename type >
using unref = std::remove_reference_t< type >;

template< typename type >
using uncv = std::remove_cv_t< type >;

template< typename type >
using unrefcv = uncv< unref< type > >;

template< typename type >
using add_lref = type &;

template< typename type >
using add_rref = type &&;

template< typename type >
using add_const = type const;

template< typename type >
using add_volatile = volatile type;

template< typename type, typename ...arguments >
using result_of = decltype(std::declval< type >()(std::declval< arguments >()...));

template< bool condition, typename type = void >
using enable_if = std::enable_if_t< condition, type >;

template< bool condition, typename yes, typename no >
using cond = std::conditional_t< condition, yes, no >;

template< typename type >
constexpr bool is_ref = std::is_reference< type >::value;

template< typename type >
constexpr bool is_lref = std::is_lvalue_reference< type >::value;

template< typename type >
constexpr bool is_rref = std::is_rvalue_reference< type >::value;

template< typename type >
constexpr bool is_const = std::is_const< unref< type > >::value;

template< typename type >
constexpr bool is_volatile = std::is_volatile< unref< type > >::value;

template< typename base, typename derived >
constexpr bool is_base_of = std::is_base_of< base, derived >::value;

template< typename to, typename ...from >
constexpr bool is_constructible = std::is_constructible< to, from... >::value;

template< typename to, typename from >
constexpr bool is_assignable = std::is_assignable< add_lref< to >, from >::value;

template< typename from, typename to >
using copy_lref = cond< is_lref< from >, to &, to >;

template< typename from, typename to >
using copy_rref = cond< is_rref< from >, to &&, to >;

template< typename from, typename to >
using copy_volatile = cond< is_volatile< from >, volatile to, to >;

template< typename from, typename to >
using copy_const = cond< is_const< from >, to const, to >;

template< typename from, typename to >
using copy_refcv = copy_rref< from, copy_lref< from, copy_volatile< from, copy_const< from, to > > > >;

template< bool value >
using bool_t = typename std::integral_constant< bool, value >::type;

template< std::size_t value >
using uint_t = typename std::integral_constant< std::size_t, value >::type;

template< std::size_t base, bool ...results >
struct get_offset;

template<>
struct get_offset< 0 >
    : uint_t< std::numeric_limits< std::size_t >::max() >
{

};

template< std::size_t base >
struct get_offset< base >
    : uint_t< std::numeric_limits< std::size_t >::max() >
{

};

template< std::size_t base, bool ...rest >
struct get_offset< base, false, rest... >
    : get_offset< base + 1, rest... >
{

};

template< std::size_t base, bool ...rest >
struct get_offset< base, true, rest... >
    : uint_t< base >
{

};

namespace details
{

template< std::size_t index, typename ...types >
struct nth_type;

template< std::size_t index >
struct nth_type< index >
{

};

template< std::size_t index, typename first, typename ...rest >
struct nth_type< index, first, rest... >
        : nth_type< index - 1, rest... >
{

};

template< typename first, typename ...rest >
struct nth_type< 0, first, rest... >
{

    using type = first;

};

}

template< std::size_t index, typename ...types >
using nth_type = typename details::nth_type< index, types... >::type;

template< bool ...values >
struct and_;

template<>
struct and_<>
        : bool_t< true >
{

};

template< bool ...values >
struct and_< true, values... >
        : and_< values... >
{

};

template< bool ...values >
struct and_< false, values... >
        : bool_t< false >
{

};

template< bool ...values >
constexpr bool all_of = and_< values... >::value;

template< bool ...values >
struct or_;

template<>
struct or_<>
        : bool_t< false >
{

};

template< bool ...values >
struct or_< false, values... >
        : or_< values... >
{

};

template< bool ...values >
struct or_< true, values... >
        : bool_t< true >
{

};

template< bool ...values >
constexpr bool any_of = or_< values... >::value;

namespace details
{

template< typename first, typename ...rest >
struct is_same;

template< typename last >
struct is_same< last >
        : bool_t< true >
{

};

template< typename next, typename ...rest >
struct is_same< next, next, rest... >
        : is_same< next, rest... >
{

};

template< typename first, typename second, typename ...rest >
struct is_same< first, second, rest... >
        : bool_t< false >
{

};

}

template< typename first, typename ...rest >
constexpr bool is_same = details::is_same< first, rest... >::value;

template< typename first, typename second >
constexpr bool is_similar = std::is_same< unrefcv< first >, second >::value;

namespace details
{

template< typename what, typename ...where >
struct contained;

template< typename what >
struct contained< what >
        : bool_t< false >
{

};

template< typename what, typename ...where >
struct contained< what, what, where... >
        : bool_t< true >
{

};

template< typename what, typename other, typename ...where >
struct contained< what, other, where... >
        : contained< what, where... >
{

};

}

template< typename what, typename ...where >
constexpr bool contained = details::contained< what, where... >::value;

}
