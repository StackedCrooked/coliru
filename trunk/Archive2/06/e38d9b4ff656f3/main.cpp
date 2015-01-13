#pragma once

#include "traits.hpp"

#include <memory>
#include <utility>

namespace insituc
{

template< typename wrapped_type >
struct recursive_wrapper final
{

    static_assert(!is_ref< wrapped_type >);
    static_assert(!is_const< wrapped_type >);
    static_assert(!is_volatile< wrapped_type >);

    using type = wrapped_type;

    ~recursive_wrapper() noexcept = default;

    template< typename first, typename ...rest >
    recursive_wrapper(first && _first, rest &&... _rest)
        : storage_(std::make_unique< type >(std::forward< first >(_first), std::forward< rest >(_rest)...))
    { ; }

    recursive_wrapper()
        : storage_(std::make_unique< type >())
    { ; }

    recursive_wrapper(recursive_wrapper const & _rhs)
        : recursive_wrapper(_rhs.get())
    { ; }

    recursive_wrapper(recursive_wrapper & _rhs)
        : recursive_wrapper(_rhs.get())
    { ; }

    recursive_wrapper(recursive_wrapper && _rhs) noexcept
        : recursive_wrapper(std::move(_rhs).get())
    { ; }

    recursive_wrapper &
    operator = (recursive_wrapper const & _rhs)
    {
        get() = _rhs.get();
    }

    recursive_wrapper &
    operator = (recursive_wrapper & _rhs)
    {
        get() = _rhs.get();
    }

    recursive_wrapper &
    operator = (recursive_wrapper && _rhs) noexcept
    {
        get() = std::move(_rhs).get();
    }

    recursive_wrapper &
    operator = (type const & _rhs)
    {
        get() = _rhs;
        return *this;
    }

    recursive_wrapper &
    operator = (type & _rhs)
    {
        get() = _rhs;
        return *this;
    }

    recursive_wrapper &
    operator = (type && _rhs) noexcept
    {
        get() = std::move(_rhs);
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
        return get();
    }

    explicit
    operator type & () &
    {
        return get();
    }

    explicit
    operator type && () &&
    {
        return std::move(get());
    }

private :

    std::unique_ptr< type > storage_;

};

template< typename type >
struct is_recursive_wrapper
        : bool_t< false >
{

};

template< typename wrapped_type >
struct is_recursive_wrapper< recursive_wrapper< wrapped_type > >
        : bool_t< true >
{

};

namespace details
{

template< typename nonwrapped, typename model >
struct unwrap_type
{

    using type = model;

    model
    operator () (model _value) const noexcept
    {
        return static_cast< model >(_value);
    }

};

template< typename wrapped, typename model >
struct unwrap_type< recursive_wrapper< wrapped >, model >
{

    using type = copy_refcv< model, wrapped >;

    type
    operator () (model _value) const noexcept
    {
        return static_cast< type >(std::forward< model >(_value).get());
    }

};

}

template< typename wrapped >
using unwrap_type = typename details::unwrap_type< unrefcv< wrapped >, wrapped >::type;

template< typename type >
decltype(auto)
unwrap(type && _value) noexcept
{
    details::unwrap_type< unrefcv< type >, type && > unwrap_type_;
    return unwrap_type_(std::forward< type >(_value));
}

template< typename wrapped_type >
void
swap(recursive_wrapper< wrapped_type > & _lhs, recursive_wrapper< wrapped_type > & _rhs) noexcept
{
    _lhs.swap(_rhs);
}

}
