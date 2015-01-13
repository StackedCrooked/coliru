#pragma once

#include "traits.hpp"
#include "variant.hpp"

#include <utility>

namespace insituc
{

namespace details
{

template< typename type, bool = is_variant< unrefcv< type > >::value >
struct underlying_type;

template< typename visitable >
struct underlying_type< visitable, true >
{

    using type = copy_refcv< visitable &&, typename unref< visitable >::template type< 0 > >; // refcv qualified first bounded type

};

template< typename nonvisitable >
struct underlying_type< nonvisitable, false >
{

    using type = nonvisitable &&;

};

template< typename visitable >
using equivalent_type = typename underlying_type< visitable >::type;

template< typename result_type, typename supervisitor, typename type, bool = is_variant< unrefcv< type > >::value >
struct subvisitor;

template< typename result_type, typename supervisitor, typename visitable >
struct subvisitor< result_type, supervisitor, visitable, true >
{ // visitation

    template< typename ...visited >
    result_type
    operator () (visited &&... _visited) const
    {
        return std::forward< visitable >(visitable_).apply_visitor(std::forward< supervisitor >(supervisitor_), std::forward< visited >(_visited)...);
    }

    supervisitor && supervisitor_;
    visitable && visitable_;

};

template< typename result_type, typename supervisitor, typename type >
struct subvisitor< result_type, supervisitor, type, false >
{ // forwarding

    template< typename ...visited >
    result_type
    operator () (visited &&... _visited) const
    {
        return std::forward< supervisitor >(supervisitor_)(std::forward< type >(value_), std::forward< visited >(_visited)...);
    }

    supervisitor && supervisitor_;
    type && value_;

};

template< typename result_type, typename ...visitables >
struct visitor_partially_applier;

template< typename result_type >
struct visitor_partially_applier< result_type >
{ // backward

    template< typename visitor >
    result_type
    operator () (visitor && _visitor) const
    {
        return std::forward< visitor >(_visitor)();
    }

};

template< typename result_type, typename first, typename ...rest >
struct visitor_partially_applier< result_type, first, rest... >
        : visitor_partially_applier< result_type, rest... >
{ // forward

    using base = visitor_partially_applier< result_type, rest... > const;

    template< typename visitor >
    result_type
    operator () (visitor && _visitor, first && _first, rest &&... _rest) const
    {
        subvisitor< result_type, visitor, first > const subvisitor_{std::forward< visitor >(_visitor), std::forward< first >(_first)};
        return base::operator () (subvisitor_, std::forward< rest >(_rest)...);
    }

};

}

template< typename visitor, typename first, typename ...rest >
decltype(auto)
apply_visitor(visitor && _visitor, first && _first, rest &&... _rest)
{
    using result_type = result_of< visitor &&, details::equivalent_type< first >, details::equivalent_type< rest >... >;
    details::visitor_partially_applier< result_type, first, rest... > apply_visitor_partially_;
    return apply_visitor_partially_(std::forward< visitor >(_visitor), std::forward< first >(_first), std::forward< rest >(_rest)...);
}

namespace details
{

template< typename visitor >
struct delayed_visitor_applier
{

    static_assert(!is_rref< visitor >);

    constexpr
    delayed_visitor_applier(visitor && _visitor) noexcept
        : visitor_(std::forward< visitor >(_visitor))
    { ; }

    template< typename visitable,
              typename = enable_if< is_variant< unrefcv< visitable > >::value > >
    decltype(auto)
    operator () (visitable && _visitable) const
    {
        return std::forward< visitable >(_visitable).apply_visitor(visitor_);
    }

    template< typename visitable,
              typename = enable_if< is_variant< unrefcv< visitable > >::value > >
    decltype(auto)
    operator () (visitable && _visitable)
    {
        return std::forward< visitable >(_visitable).apply_visitor(visitor_);
    }

    template< typename ...visitables >
    decltype(auto)
    operator () (visitables &&... _visitables) const
    {
        return apply_visitor(visitor_, std::forward< visitables >(_visitables)...);
    }

    template< typename ...visitables >
    decltype(auto)
    operator () (visitables &&... _visitables)
    {
        return apply_visitor(visitor_, std::forward< visitables >(_visitables)...);
    }

private :

    visitor visitor_;

};

}

template< typename visitor >
constexpr
details::delayed_visitor_applier< visitor >
apply_visitor(visitor && _visitor) noexcept
{
    return std::forward< visitor >(_visitor);
}

}
