#pragma once

#include "traits.hpp"

#include <memory>

namespace std
{

template< typename T, typename ...Args >
unique_ptr< T >
make_unique(Args &&... _args)
{
    return unique_ptr< T >(new T(forward< Args >(_args)...));
}

} // namespace std

namespace insituc
{

namespace details
{

template< typename ...visitables >
struct visitor_partially_applier;

template< typename visitor >
struct delayed_visitor_applier;

} // namespace details

template< typename type >
struct recursive_wrapper;

template< typename type >
void
swap(recursive_wrapper< type > & _lhs, recursive_wrapper< type > & _rhs) noexcept;

struct bad_get;

template< typename ...types >
struct variant;

template< typename type >
struct is_variant;

template< typename ...lhs_types, typename ...rhs_types >
void
swap(variant< lhs_types... > & _lhs, variant< rhs_types... > & _rhs) noexcept;

template< typename variant, typename ...arguments >
variant
make_variant(arguments &&... _arguments);

template< typename type, typename ...types >
type const &
get(variant< types... > const & _variant);

template< typename type, typename ...types >
type &
get(variant< types... > & _variant);

template< typename visitor, typename first, typename ...rest >
result_of< details::visitor_partially_applier< first, rest... > const, visitor, first, rest... >
apply_visitor(visitor && _visitor, first && _first, rest &&... _rest);

template< typename visitor >
constexpr
details::delayed_visitor_applier< visitor >
apply_visitor(visitor && _visitor);

template< typename ...lhs_types, typename ...rhs_types >
bool
operator == (variant< lhs_types... > const & _lhs, variant< rhs_types... > const & _rhs);

template< typename ...lhs_types, typename ...rhs_types >
bool
operator < (variant< lhs_types... > const & _lhs, variant< rhs_types... > const & _rhs);

} // namespace insituc
