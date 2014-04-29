#pragma once

#include "traits.hpp"
#include "variant_fwd.hpp"

#include <memory>

namespace insituc
{

template< typename wrapped_type >
struct recursive_wrapper
{

    static_assert(!std::is_reference< wrapped_type >::value,
                  "type should not be a reference");

    static_assert(!std::is_const< wrapped_type >::value,
                  "type should not be a const");

    static_assert(!std::is_volatile< wrapped_type >::value,
                  "type should not be a volatile");

    using type = wrapped_type;

    ~recursive_wrapper() noexcept = default;

    template< typename ...arguments >
    recursive_wrapper(arguments &&... _arguments)
        : storage_(std::make_unique< type >(std::forward< arguments >(_arguments)...))
    { ; }

    recursive_wrapper()
        : storage_(std::make_unique< type >())
    { ; }

    recursive_wrapper(recursive_wrapper const & _rhs)
        : recursive_wrapper(_rhs.get())
    { ; }

    recursive_wrapper(recursive_wrapper && _rhs) noexcept
        : recursive_wrapper(std::move(_rhs).get())
    { ; }

    recursive_wrapper(type const & _rhs)
        : recursive_wrapper(_rhs)
    { ; }

    recursive_wrapper(type && _rhs)
        : recursive_wrapper(std::move(_rhs))
    { ; }

    recursive_wrapper &
    operator = (recursive_wrapper const & _rhs)
    {
        get() = _rhs.get();
    }

    recursive_wrapper &
    operator = (recursive_wrapper && _rhs)
    {
        get() = std::move(_rhs).get();
    }

    recursive_wrapper &
    operator = (type const & _rhs)
    {
        *storage_ = _rhs;
        return *this;
    }

    recursive_wrapper &
    operator = (type && _rhs)
    {
        *storage_ = std::move(_rhs);
        return *this;
    }

    void
    swap(recursive_wrapper & _rhs) noexcept
    {
        std::swap(storage_, _rhs.storage_);
    }

    type const &
    get() const &
    {
        return *storage_;
    }

    type &
    get() &
    {
        return *storage_;
    }

    type &&
    get() &&
    {
        return std::move(*storage_);
    }

    explicit
    operator type const & () const &
    {
        return *storage_;
    }

    explicit
    operator type & () &
    {
        return *storage_;
    }

    explicit
    operator type && () &&
    {
        return std::move(*storage_);
    }

private :

    std::unique_ptr< type > storage_;

};

template< typename type >
struct is_recursive_wrapper
        : bool_< false >
{

};

template< typename wrapped_type >
struct is_recursive_wrapper< recursive_wrapper< wrapped_type > >
        : bool_< true >
{

};

namespace details
{

template< typename nonwrapped_type >
struct unwrap_type
{

    using type = nonwrapped_type;

};

template< typename wrapped_type >
struct unwrap_type< recursive_wrapper< wrapped_type > >
{

    using type = wrapped_type;

};

} // namespace details

template< typename wrapped_type >
using unwrap_type = typename details::unwrap_type< wrapped_type >::type;

template< typename nonwrapped_type >
constexpr
nonwrapped_type &&
unwrap(nonwrapped_type && _nonwrapped)
{
    return std::forward< nonwrapped_type >(_nonwrapped);
}

template< typename wrapped_type >
wrapped_type const &
unwrap(recursive_wrapper< wrapped_type > const & _wrapped)
{
    return static_cast< wrapped_type const & >(_wrapped);
}

template< typename wrapped_type >
wrapped_type &
unwrap(recursive_wrapper< wrapped_type > & _wrapped)
{
    return static_cast< wrapped_type & >(_wrapped);
}

template< typename wrapped_type >
wrapped_type &&
unwrap(recursive_wrapper< wrapped_type > && _wrapped)
{
    return static_cast< wrapped_type && >(_wrapped);
}

template< typename type >
void
swap(recursive_wrapper< type > & _lhs, recursive_wrapper< type > & _rhs) noexcept
{
    _lhs.swap(_rhs);
}

} // namespace insituc