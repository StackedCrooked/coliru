#pragma once

#include <type_traits>

namespace insituc
{

template< typename type >
using unref = typename std::remove_reference< type >::type;

template< typename type >
using uncv = typename std::remove_cv< type >::type;

template< typename type >
using unrefcv = uncv< unref< type > >;

template< typename type, typename ...arguments >
using result_of = typename std::result_of< type(arguments...) >::type;

template< bool condition, typename type = void >
using enable_if = typename std::enable_if< condition, type >::type;

template< bool condition, typename yes, typename no >
using cond = typename std::conditional< condition, yes, no >::type;

template< typename type >
using is_const = typename std::is_const< unref< type > >::type;

template< typename type >
using is_volatile = typename std::is_volatile< unref< type > >::type;

template< typename from, typename to >
using copy_lref = cond< std::is_lvalue_reference< from >::value, typename std::add_lvalue_reference< to >::type, to >;

template< typename from, typename to >
using copy_rref = cond< std::is_rvalue_reference< from >::value, typename std::add_rvalue_reference< to >::type, to >;

template< typename from, typename to >
using copy_volatile = cond< is_volatile< from >::value, typename std::add_volatile< to >::type, to >;

template< typename from, typename to >
using copy_const = cond< is_const< from >::value, typename std::add_const< to >::type, to >;

template< typename from, typename to >
using copy_cvref = copy_lref< from, copy_rref< from, copy_volatile< from, copy_const< from, to > > > >;

template< bool value >
using bool_ = typename std::integral_constant< bool, value >::type;

template< int value >
using int_ = typename std::integral_constant< int, value >::type;

template< typename type, type ...values >
struct max_value;

template< typename type, type last >
struct max_value< type, last >
    : int_< last >
{

};

template< typename type, type first, type second >
struct max_value< type, first, second >
	: int_< (first < second) ? second : first >
{

};

template< typename type, type first, type ...rest >
struct max_value< type, first, rest... >
	: max_value< type, first, max_value< type, rest... >::value >
{

};

template< int base, bool ...results >
struct get_offset;

template< int base >
struct get_offset< base >
	: int_< -1 >
{

};

template< int base >
struct get_offset< base, false >
	: int_< -1 >
{

};

template< int base, bool ...rest >
struct get_offset< base, false, rest... >
	: get_offset< base + 1, rest... >
{

};

template< int base, bool ...rest >
struct get_offset< base, true, rest... >
	: int_< base >
{

};

template< int index, typename ...types >
struct nth_type;

template< int index >
struct nth_type< index >
{

    static_assert(!(index < 0), "index is greater then number of types");

};

template< int index, typename first, typename ...rest >
struct nth_type< index, first, rest... >
{

    static_assert(!(index < 0), "index is negative");

    using type = typename nth_type< index - 1, rest... >::type;

};

template< typename first, typename ...rest >
struct nth_type< 0, first, rest... >
{

    using type = first;

};

template< bool first, bool ...rest >
struct and_;

template< bool next, bool ...rest >
struct and_< true, next, rest... >
        : and_< next, rest... >
{

};

template< bool ...rest >
struct and_< false, rest... >
        : bool_< false >
{

};

template< bool last>
struct and_< last >
        : bool_< last >
{

};

template< bool first, bool ...rest >
struct or_;

template< bool next, bool ...rest >
struct or_< false, next, rest... >
        : or_< next, rest... >
{

};

template< bool ...rest >
struct or_< true, rest... >
        : bool_< true >
{

};

template<>
struct or_< false >
        : bool_< false >
{

};

template< typename first, typename ...rest >
struct is_same;

template< typename last >
struct is_same< last >
        : bool_< true >
{

};

template< typename next, typename ...rest >
struct is_same< next, next, rest... >
        : is_same< next, rest... >
{

};

template< typename first, typename second, typename ...rest >
struct is_same< first, second, rest... >
        : bool_< false >
{

};

} // namespace insituc
