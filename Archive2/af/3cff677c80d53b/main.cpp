#pragma once

#include "variant_fwd.hpp"
#include "traits.hpp"

#include <type_traits>

namespace insituc
{

namespace details
{

template< typename visitor >
using cvref_qualified_first_type = copy_cvref< visitor, typename unref< visitor >::template type< 0 > >;

template< typename supervisitor, typename type, bool = is_variant< unrefcv< type > >::value >
struct subvisitor;

template< typename supervisitor, typename visitable >
struct subvisitor< supervisitor, visitable, true >
{ // visit

    template< typename ...visited >
    result_of< supervisitor, cvref_qualified_first_type< visitable >, visited... >
    operator () (visited &&... _visited) const
    {
        return std::forward< visitable >(visitable_).apply_visitor(std::forward< supervisitor >(supervisitor_), std::forward< visited >(_visited)...);
    }

    supervisitor && supervisitor_;
    visitable && visitable_;

};

template< typename supervisitor, typename type >
struct subvisitor< supervisitor, type, false >
{ // pass

    template< typename ...visited >
    result_of< supervisitor, type, visited... >
    operator () (visited &&... _visited) const
    {
        return std::forward< supervisitor >(supervisitor_)(std::forward< type >(value_), std::forward< visited >(_visited)...);
    }

    supervisitor && supervisitor_;
    type && value_;

};

template< typename ...visitables >
struct visitor_partially_applier;

template<>
struct visitor_partially_applier<>
{ // backward

    template< typename visitor >
    result_of< visitor >
    operator () (visitor && _visitor) const
    {
        return std::forward< visitor >(_visitor)();
    }

};

template< typename first, typename ...rest >
struct visitor_partially_applier< first, rest... >
        : visitor_partially_applier< rest... >
{ // forward

    using base = visitor_partially_applier< rest... >;

    template< typename visitor >
    result_of< base, subvisitor< visitor, first >, rest... >
    operator () (visitor && _visitor, first && _first, rest &&... _rest) const
    {
        subvisitor< visitor, first > const subvisitor_{std::forward< visitor >(_visitor), std::forward< first >(_first)};
        return base::operator () (subvisitor_, std::forward< rest >(_rest)...);
    }

};

} // namespace details

template< typename visitor, typename first, typename ...rest >
//constexpr // C++14 // body of constexpr function not a return-statement
result_of< details::visitor_partially_applier< first, rest... > const, visitor, first, rest... >
apply_visitor(visitor && _visitor, first && _first, rest &&... _rest) // visitables can contain non-visitor types
{
    details::visitor_partially_applier< first, rest... > const apply_visitor_partially_;
    return apply_visitor_partially_(std::forward< visitor >(_visitor), std::forward< first >(_first), std::forward< rest >(_rest)...);
}

namespace details
{

template< typename visitor >
struct delayed_visitor_applier
{

    delayed_visitor_applier(visitor && _visitor)
        : visitor_(std::forward< visitor >(_visitor))
    { ; }

    template< typename visitable >
    result_of< visitor, cvref_qualified_first_type< visitable > >
    operator () (visitable && _visitable) const
    {
        return std::forward< visitable >(_visitable).apply_visitor(visitor_);
    }

    template< typename ...visitables >
    result_of< details::visitor_partially_applier< visitables... > const, visitor, visitables... >
    operator () (visitables &&... _visitables) const
    {
        return apply_visitor(visitor_, std::forward< visitables >(_visitables)...);
    }

private :

    visitor visitor_;

};

} // namespace details

template< typename visitor >
constexpr
details::delayed_visitor_applier< visitor >
apply_visitor(visitor && _visitor)
{
    return details::delayed_visitor_applier< visitor >(std::forward< visitor >(_visitor));
}

} // namespace insituc
