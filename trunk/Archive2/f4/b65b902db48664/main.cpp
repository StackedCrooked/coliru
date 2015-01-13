#pragma once

#include "traits.hpp"
#include "recursive_wrapper.hpp"

#include <stdexcept>
#include <memory>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <algorithm>
#include <functional>

#include <cstdlib>

namespace insituc
{

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
struct bad_get
        : std::runtime_error
{

    explicit
    bad_get(const char * _what)
        : std::runtime_error(_what)
    { ; }

    explicit
    bad_get(std::string const & _what)
        : std::runtime_error(_what)
    { ; }

};
#pragma clang diagnostic pop

template< typename ...types >
struct variant final
{

    using size_type = std::size_t;

    static_assert(all_of< !is_ref< types >... >);
    static_assert(all_of< !is_const< types >... >);
    static_assert(all_of< !is_volatile< types >... >);

    static constexpr size_type npos = get_offset< 0 >::value;

    template< typename type >
    using which_type = get_offset< 0, is_same< type, unwrap_type< types > >... >;

    template< size_type _which >
    using type = nth_type< _which, unwrap_type< types >... >;

    using types_count = uint_t< sizeof...(types) >;

    template< typename type >
    using is_this_type = bool_t< (which_type< unrefcv< type > >::value != npos) >;

    template< typename ...arguments >
    using which_is_constructible = get_offset< 0, is_constructible< unwrap_type< types >, arguments... >... >;

    template< typename type >
    using which_is_assignable = get_offset< 0, is_assignable< unwrap_type< types >, type >... >;

    template< typename ...arguments >
    using is_there_constructible = or_< is_constructible< unwrap_type< types >, arguments... >... >;

    template< typename type >
    using is_there_assignable = or_< is_assignable< unwrap_type< types >, type >... >;

    using reference = variant< std::reference_wrapper< unwrap_type< types > >... >;

private :

    template< size_type _which >
    using internal_type = nth_type< _which, types... >;

    using storage_type = std::aligned_union_t< 0, types... >;
    std::unique_ptr< storage_type > storage_ = std::make_unique< storage_type >();
    size_type which_ = npos;

    template< typename result_type, typename storage, typename visitor, typename type, typename ...arguments >
    static
    result_type
    caller(storage && _storage, visitor && _visitor, arguments &&... _arguments)
    {
        return std::forward< visitor >(_visitor)(unwrap(reinterpret_cast< type && >(_storage)), std::forward< arguments >(_arguments)...);
    }

    struct destroyer
    {

        template< typename type >
        void
        operator () (type & _value) const
        {
            _value.~type();
        }

    };

    template< typename rhs >
    enable_if< is_this_type< unrefcv< rhs > >::value >
    construct(rhs && _rhs)
    {
        static_assert(is_constructible< unrefcv< rhs >, rhs && >,
                      "type selected, but it cannot be constructed");
        constexpr size_type _which = which_type< unrefcv< rhs > >::value;
        ::new (storage_.get()) internal_type< _which >(std::forward< rhs >(_rhs));
        which_ = _which;
    }

    template< typename ...arguments >
    void
    construct(arguments &&... _arguments)
    {
        constexpr size_type _which = which_is_constructible< arguments &&... >::value;
        static_assert((_which != npos),
                      "no one type can be constructed from specified parameter pack");
        // -Wconversion warning here means, that construction or assignment may imply undesirable type conversion
        ::new (storage_.get()) internal_type< _which >(std::forward< arguments >(_arguments)...);
        which_ = _which;
    }

    struct constructor
    {

        template< typename rhs >
        void
        operator () (rhs && _rhs) const
        {
            destination_.construct(std::forward< rhs >(_rhs));
        }

        variant & destination_;

    };

    struct assigner
    {

        template< typename lhs, typename rhs >
        constexpr
        enable_if< is_constructible< lhs, rhs && > >
        reconstruct(rhs && _rhs) const noexcept
        {
            variant backup_(std::forward< rhs >(_rhs));
            lhs_.swap(backup_);
        }

        template< typename lhs, typename rhs >
        constexpr
        enable_if< !is_constructible< lhs, rhs && > >
        reconstruct(rhs &&) const
        {
            throw bad_get("assigner: lhs is not constructible from rhs");
        }

        template< typename lhs, typename rhs >
        constexpr
        enable_if< is_assignable< lhs, rhs && > >
        reassign(rhs && _rhs) const
        {
            // -Wconversion warning here means, that assignment may imply undesirable type conversion
            lhs_.get< lhs >() = std::forward< rhs >(_rhs);
        }

        template< typename lhs, typename rhs >
        constexpr
        enable_if< !is_assignable< lhs, rhs && > >
        reassign(rhs && _rhs) const
        {
            reconstruct< lhs >(std::forward< rhs >(_rhs));
        }

        template< typename rhs >
        constexpr
        enable_if< is_this_type< unrefcv< rhs > >::value >
        operator () (rhs && _rhs) const
        {
            using lhs = unrefcv< rhs >;
            static_assert((is_assignable< lhs, rhs && > || is_constructible< lhs, rhs && >),
                          "type selected, but it cannot be assigned");
            if (lhs_.which() == which_type< lhs >::value) {
                reassign< lhs >(std::forward< rhs >(_rhs));
            } else {
                reconstruct< lhs >(std::forward< rhs >(_rhs));
            }
        }

        template< typename rhs >
        constexpr
        enable_if< is_there_constructible< rhs && >::value >
        construct(rhs && _rhs) const noexcept
        {
            variant backup_(std::forward< rhs >(_rhs));
            lhs_.swap(backup_);
        }

        template< typename rhs >
        constexpr
        enable_if< !is_there_constructible< rhs && >::value >
        construct(rhs &&) const
        {
            throw bad_get("assigner: there is no constructible from rhs at all");
        }

        template< typename rhs >
        constexpr
        enable_if< (!is_this_type< unrefcv< rhs > >::value && is_there_assignable< rhs && >::value) >
        operator () (rhs && _rhs) const
        {
            constexpr size_type _which = which_is_assignable< rhs && >::value;
            if (lhs_.which() == _which) {
                // -Wconversion warning here means, that assignment may imply undesirable type conversion
                lhs_.get< type< _which > >() = std::forward< rhs >(_rhs);
            } else {
                construct(std::forward< rhs >(_rhs));
            }
        }

        template< typename rhs >
        constexpr
        enable_if< (!is_this_type< unrefcv< rhs > >::value && !is_there_assignable< rhs && >::value) >
        operator () (rhs && _rhs) const
        {
            construct(std::forward< rhs >(_rhs));
        }

        variant & lhs_;

    };

    struct reflect
    {

        template< typename type >
        std::type_info const &
        operator () (type const &) const
        {
            return typeid(type);
        }

    };

public :

    ~variant() noexcept(and_< std::is_nothrow_destructible< types >::value... >::value)
    {
        apply_visitor(destroyer{});
    }

    void
    swap(variant & _other) noexcept
    {
        storage_.swap(_other.storage_);
        std::swap(which_, _other.which_);
    }

    size_type
    which() const
    {
        return which_;
    }

    template< typename visitor, typename ...arguments >
    decltype(auto)
    apply_visitor(visitor && _visitor, arguments &&... _arguments) const &
    {
        static_assert(is_same< result_of< visitor &&, unwrap_type< types > const &, arguments &&... >... >,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor &&, type< 0 > const &, arguments &&... >;
        using caller_type = result_type (*)(storage_type const & _storage, visitor && _visitor, arguments &&... _arguments);
        static constexpr caller_type dispatcher_[sizeof...(types)] = {&variant::caller< result_type, storage_type const &, visitor, types const &, arguments... >...};
        return dispatcher_[which_](*storage_, std::forward< visitor >(_visitor), std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename ...arguments >
    decltype(auto)
    apply_visitor(visitor && _visitor, arguments &&... _arguments) &
    {
        static_assert(is_same< result_of< visitor &&, unwrap_type< types > &, arguments &&... >... >,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor &&, type< 0 > &, arguments &&... >;
        using caller_type = result_type (*)(storage_type & _storage, visitor && _visitor, arguments &&... _arguments);
        static constexpr caller_type dispatcher_[sizeof...(types)] = {&variant::caller< result_type, storage_type &, visitor, types &, arguments... >...};
        return dispatcher_[which_](*storage_, std::forward< visitor >(_visitor), std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename ...arguments >
    decltype(auto)
    apply_visitor(visitor && _visitor, arguments &&... _arguments) &&
    {
        static_assert(is_same< result_of< visitor &&, unwrap_type< types > &&, arguments &&... >... >,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor &&, type< 0 > &&, arguments &&... >;
        using caller_type = result_type (*)(storage_type && _storage, visitor && _visitor, arguments &&... _arguments);
        static constexpr caller_type dispatcher_[sizeof...(types)] = {&variant::caller< result_type, storage_type &&, visitor, types &&, arguments... >...};
        return dispatcher_[which_](std::move(*storage_), std::forward< visitor >(_visitor), std::forward< arguments >(_arguments)...);
    }

    variant()
    {
        static_assert(is_there_constructible<>::value,
                      "no one type is default constructible");
        construct();
    }

    variant(variant const & _rhs)
    {
        _rhs.apply_visitor(constructor{*this});
    }

    variant(variant & _rhs)
    {
        _rhs.apply_visitor(constructor{*this});
    }

    variant(variant && _rhs) noexcept
    {
        std::move(_rhs).apply_visitor(constructor{*this});
    }

    template< typename ...other_types >
    variant(variant< other_types... > const & _rhs)
    {
        _rhs.apply_visitor(constructor{*this});
    }

    template< typename ...other_types >
    variant(variant< other_types... > & _rhs)
    {
        _rhs.apply_visitor(constructor{*this});
    }

    template< typename ...other_types >
    variant(variant< other_types... > && _rhs)
    {
        std::move(_rhs).apply_visitor(constructor{*this});
    }

    template< typename first, typename ...rest >
    variant(first && _first, rest &&... _rest)
    {
        construct< first, rest... >(std::forward< first >(_first), std::forward< rest >(_rest)...);
    }

    variant &
    operator = (variant const & _rhs)
    {
        _rhs.apply_visitor(assigner{*this});
        return *this;
    }

    variant &
    operator = (variant & _rhs)
    {
        _rhs.apply_visitor(assigner{*this});
        return *this;
    }

    variant &
    operator = (variant && _rhs) noexcept
    {
        std::move(_rhs).apply_visitor(assigner{*this});
        return *this;
    }

    template< typename ...other_types >
    variant &
    operator = (variant< other_types... > const & _rhs)
    {
        _rhs.apply_visitor(assigner{*this});
        return *this;
    }

    template< typename ...other_types >
    variant &
    operator = (variant< other_types... > & _rhs)
    {
        _rhs.apply_visitor(assigner{*this});
        return *this;
    }

    template< typename ...other_types >
    variant &
    operator = (variant< other_types... > && _rhs)
    {
        std::move(_rhs).apply_visitor(assigner{*this});
        return *this;
    }

    template< typename rhs >
    variant &
    operator = (rhs && _rhs)
    {
        static_assert((is_this_type< unrefcv< rhs > >::value || (is_there_assignable< rhs && >::value || is_there_constructible< rhs && >::value)),
                      "no one underlying type is proper to assignment");
        assigner{*this}(std::forward< rhs >(_rhs));
        return *this;
    }

    template< typename type >
    type const &
    get() const &
    {
        constexpr size_type _which = which_type< type >::value;
        static_assert((_which != npos), "specified type is not in the list");
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > const & >(*storage_));
        }
    }

    template< size_type _which >
    decltype(auto)
    get() const &
    {
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > const & >(*storage_));
        }
    }

    template< typename type >
    type &
    get() &
    {
        constexpr size_type _which = which_type< type >::value;
        static_assert((_which != npos), "specified type is not in the list");
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > & >(*storage_));
        }
    }

    template< size_type _which >
    decltype(auto)
    get() &
    {
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > & >(*storage_));
        }
    }

    template< typename type >
    type &&
    get() &&
    {
        constexpr size_type _which = which_type< type >::value;
        static_assert((_which != npos), "specified type is not in the list");
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > && >(*storage_));
        }
    }

    template< size_type _which >
    decltype(auto)
    get() &&
    {
        if (which_ != _which) {
            throw bad_get("get: containing type does not match requested type");
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > && >(*storage_));
        }
    }

    std::type_info const &
    get_type_info() const
    {
        return apply_visitor(reflect{});
    }

};

template<>
struct variant<>; // Intentionally declared but not defined. This leaves open the possibility to define a meaningful specialization by yourself.

template< typename variant_type, typename type >
constexpr
typename variant_type::size_type
which_bounded_type = variant_type::template which_type< type >::value;

template< typename type >
struct is_variant
        : bool_t< false >
{

};

template< typename first, typename ...rest >
struct is_variant< variant< first, rest... > >
        : bool_t< true >
{

};

template< typename type >
constexpr bool is_variant_v = is_variant< unrefcv< type > >::value;

template< typename ...types >
void
swap(variant< types... > & _lhs, variant< types... > & _rhs) noexcept
{
    _lhs.swap(_rhs);
}

template< typename variant, typename ...arguments >
variant
make_variant(arguments &&... _arguments)
{
    return {std::forward< arguments >(_arguments)...};
}

template< typename type, typename ...types >
type const &
get(variant< types... > const & _variant)
{
    return _variant.template get< type >();
}

template< typename type, typename ...types >
type &
get(variant< types... > & _variant)
{
    return _variant.template get< type >();
}

template< typename type, typename ...types >
type &&
get(variant< types... > && _variant)
{
    return std::move(_variant).template get< type >();
}

}
