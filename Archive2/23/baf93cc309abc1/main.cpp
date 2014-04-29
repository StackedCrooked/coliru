#pragma once

#include "traits.hpp"
#include "variant_fwd.hpp"
#include "recursive_wrapper.hpp"

#include <memory>
#include <type_traits>
#include <exception>

namespace insituc
{

struct bad_get
        : std::exception
{

    virtual
    ~bad_get() = default;

    bad_get() = default;

    bad_get(const char * const _what)
        : std::exception()
        , what_(_what)
    { ; }

    virtual
    const char *
    what() const noexcept
    {
        return what_;
    }

private :

    const char * const what_ = "bad_get: failed value get using get()";

};

template< typename ...types >
struct variant
{

    static_assert((0 < sizeof...(types)),
                  "types list should not be empty");

    static_assert(and_< !std::is_reference< types >::value... >::value,
                  "types list should not contain a reference");

    static_assert(and_< !std::is_const< types >::value... >::value,
                  "types list should not contain a const");

    static_assert(and_< !std::is_volatile< types >::value... >::value,
                  "types list should not contain a volatile");

    template< typename type >
    using which_type = get_offset< 0, is_same< type, unwrap_type< types > >::value... >;

    template< int _which >
    using type = typename nth_type< _which, unwrap_type< types >... >::type;

    using types_count = int_< sizeof...(types) >;

private :

    template< typename type >
    using is_this_type = bool_< !(which_type< unrefcv< type > >::value < 0) >;

    template< int _which >
    using internal_type = typename nth_type< _which, types... >::type;

    template< typename ...arguments >
    using which_is_constructible_from = get_offset< 0, std::is_constructible< unwrap_type< types >, arguments... >::value... >;

    template< typename type >
    using which_is_assignable_from = get_offset< 0, std::is_assignable< unwrap_type< types > &, type >::value... >;

    template< typename ...arguments >
    using is_there_constructible = or_< std::is_constructible< unwrap_type< types >, arguments... >::value... >;

    template< typename type >
    using is_there_assignable = or_< std::is_assignable< unwrap_type< types > &, type >::value... >;

    constexpr static std::size_t const size = max_value< std::size_t, sizeof(types)... >::value;
    constexpr static std::size_t const align = max_value< std::size_t, alignof(types)... >::value;
    using storage_type = typename std::aligned_storage< size, align >::type; // std::aligned_union would be better to use
    std::unique_ptr< storage_type > storage_ = std::make_unique< storage_type >();
    int which_ = -1;

    template< typename visitor, typename type, typename ...arguments >
    result_of< visitor, unwrap_type< type >, arguments... >
    caller(visitor && _visitor, arguments &&... _arguments) const &
    {
        return std::forward< visitor >(_visitor)(unwrap(reinterpret_cast< type >(*storage_)), std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename type, typename ...arguments >
    result_of< visitor, unwrap_type< type >, arguments... >
    caller(visitor && _visitor, arguments &&... _arguments) &
    {
        return std::forward< visitor >(_visitor)(unwrap(reinterpret_cast< type >(*storage_)), std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename type, typename ...arguments >
    result_of< visitor, unwrap_type< type >, arguments... >
    caller(visitor && _visitor, arguments &&... _arguments) &&
    {
        return std::forward< visitor >(_visitor)(unwrap(reinterpret_cast< type >(*storage_)), std::forward< arguments >(_arguments)...);
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
        static_assert(std::is_constructible< unrefcv< rhs >, rhs >::value, "type selected, but it cannot be constructed");
        constexpr int _which = which_type< unrefcv< rhs > >::value;
        ::new (storage_.get()) internal_type< _which >(std::forward< rhs >(_rhs));
        which_ = _which;
    }

    template< typename ...arguments >
    void
    construct(arguments &&... _arguments)
    {
        constexpr int _which = which_is_constructible_from< arguments... >::value;
    	static_assert(!(_which < 0), "no one type can be constructed from specified parameter pack");
        // -Wconversion warning here means, that construction or assignmnet may imply undesirable type conversion
        new (storage_.get()) internal_type< _which >(std::forward< arguments >(_arguments)...);
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

        template< int _which, typename rhs >
        void
        assign(rhs && _rhs) const
        {
            if (lhs_.which() == _which) {
                // -Wconversion warning here means, that assignment may imply undesirable type conversion
                lhs_.get< type< _which > >() = std::forward< rhs >(_rhs);
            } else {
                variant backup_(std::forward< rhs >(_rhs));
                lhs_.swap(backup_);
            }
        }

        template< typename rhs >
        enable_if< is_this_type< unrefcv< rhs > >::value >
        operator () (rhs && _rhs) const
        {
            static_assert(std::is_assignable< unrefcv< rhs > &, rhs >::value, "type selected, but it cannot be assigned");
            static_assert(std::is_constructible< unrefcv< rhs >, rhs >::value, "type selected, but it cannot be constructed");
            assign< which_type< unrefcv< rhs > >::value >(std::forward< rhs >(_rhs));
        }

        template< typename rhs >
        enable_if< (!is_this_type< unrefcv< rhs > >::value && (is_there_assignable< rhs >::value && is_there_constructible< rhs >::value)) >
        operator () (rhs && _rhs) const
        {
            assign< which_is_assignable_from< rhs >::value >(std::forward< rhs >(_rhs));
        }

        template< typename rhs >
        enable_if< (!is_this_type< unrefcv< rhs > >::value && (is_there_assignable< rhs >::value && !is_there_constructible< rhs >::value)) >
        operator () (rhs && _rhs) const
        {
            constexpr int _which = which_is_assignable_from< rhs >::value;
            if (lhs_.which() == _which) {
                // -Wconversion warning here means, that assignment may imply undesirable conversion
                lhs_.get< type< _which > >() = std::forward< rhs >(_rhs);
            } else {
                throw bad_get(__PRETTY_FUNCTION__);
            }
        }

        template< typename rhs >
        enable_if< (!is_this_type< unrefcv< rhs > >::value && (!is_there_assignable< rhs >::value && is_there_constructible< rhs >::value)) >
        operator () (rhs && _rhs) const
        {
            constexpr int _which = which_is_constructible_from< rhs >::value;
            if (lhs_.which() == _which) {
                throw bad_get(__PRETTY_FUNCTION__);
            } else {
                variant backup_(std::forward< rhs >(_rhs));
                lhs_.swap(backup_);
            }
        }

        template< typename rhs >
        enable_if< (!is_this_type< unrefcv< rhs > >::value && !(is_there_assignable< rhs >::value || is_there_constructible< rhs >::value)) >
        operator () (rhs &&) const
        {
            throw bad_get(__PRETTY_FUNCTION__);
        }

        variant & lhs_;

    };

public :

    virtual
    ~variant()
    {
        apply_visitor(destroyer{});
    }

    void
    swap(variant & _other) noexcept
    {
        storage_.swap(_other.storage_);
        std::swap(which_, _other.which_);
    }

    int
    which() const noexcept
    {
        return which_;
    }

    template< typename visitor, typename ...arguments >
    result_of< visitor, type< 0 > const &, arguments... >
    apply_visitor(visitor && _visitor, arguments &&... _arguments) const &
    {
        static_assert(is_same< result_of< visitor, unwrap_type< types > const &, arguments... >... >::value,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor, type< 0 > const &, arguments... >;
        using caller_type = result_type (variant::*)(visitor && _visitor, arguments &&... _arguments) const &;
        constexpr static caller_type const dispatcher_[sizeof...(types)] = {&variant::caller< visitor, types const &, arguments... >...};
        return (static_cast< variant const & >(*this).*dispatcher_[which_])(std::forward< visitor >(_visitor),
                                                                            std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename ...arguments >
    result_of< visitor, type< 0 > &, arguments... >
    apply_visitor(visitor && _visitor, arguments &&... _arguments) &
    {
        static_assert(is_same< result_of< visitor, unwrap_type< types > &, arguments... >... >::value,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor, type< 0 > &, arguments... >;
        using caller_type = result_type (variant::*)(visitor && _visitor, arguments &&... _arguments) &;
        constexpr static caller_type const dispatcher_[sizeof...(types)] = {&variant::caller< visitor, types &, arguments... >...};
        return (static_cast< variant & >(*this).*dispatcher_[which_])(std::forward< visitor >(_visitor),
                                                                      std::forward< arguments >(_arguments)...);
    }

    template< typename visitor, typename ...arguments >
    result_of< visitor, type< 0 > &&, arguments... >
    apply_visitor(visitor && _visitor, arguments &&... _arguments) &&
    {
        static_assert(is_same< result_of< visitor, unwrap_type< types > &&, arguments... >... >::value,
                      "non-identical return types in visitor");
        using result_type = result_of< visitor, type< 0 > &&, arguments... >;
        using caller_type = result_type (variant::*)(visitor && _visitor, arguments &&... _arguments) &&;
        constexpr static caller_type const dispatcher_[sizeof...(types)] = {&variant::caller< visitor, types &&, arguments... >...};
        return (static_cast< variant && >(*this).*dispatcher_[which_])(std::forward< visitor >(_visitor),
                                                                       std::forward< arguments >(_arguments)...);
    }

    variant()
    {
        static_assert(is_there_constructible<>::value, "no one type is default constructible");
        construct();
    }

    variant(variant const & _rhs)
    {
        _rhs.apply_visitor(constructor{*this});
    }

    variant(variant && _rhs)
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

    template< typename rhs,
              typename = enable_if< is_this_type< unrefcv< rhs > >::value > >
    variant(rhs && _rhs)
    {
        construct(std::forward< rhs >(_rhs));
    }

    // constructs value of first type, which is constructible form specified pack of arguments
    template< typename ...arguments >
	explicit
    variant(arguments &&... _arguments)
    {
		constexpr int _which = which_is_constructible_from< arguments... >::value;
		static_assert(!(_which < 0), "no one type can be constructed from specified parameter pack");
        construct(std::forward< arguments >(_arguments)...);
    }

    variant &
    operator = (variant const & _rhs)
    {
        _rhs.apply_visitor(assigner{*this});
        return *this;
    }

    variant &
    operator = (variant && _rhs)
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
        static_assert((is_this_type< unrefcv< rhs > >::value || (is_there_assignable< rhs >::value || is_there_constructible< rhs >::value)),
                      "no one underlying type is proper to assignment");
        assigner{*this}(std::forward< rhs >(_rhs));
        return *this;
    }

    template< typename type >
    type const &
    get() const &
    {
        constexpr int _which = which_type< type >::value;
        static_assert(!(_which < 0), "type is not listed");
        if (which_ != _which) {
            throw bad_get();
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > const & >(*storage_));
        }
    }

    template< typename type >
    type &
    get() &
    {
        constexpr int _which = which_type< type >::value;
        static_assert(!(_which < 0), "type is not listed");
        if (which_ != _which) {
            throw bad_get();
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > & >(*storage_));
        }
    }

    template< typename type >
    type &&
    get() &&
    {
        constexpr int _which = which_type< type >::value;
        static_assert(!(_which < 0), "type is not listed");
        if (which_ != _which) {
            throw bad_get();
        } else {
            return unwrap(reinterpret_cast< internal_type< _which > && >(*storage_));
        }
    }

	//friend
	//std::ostream &
	//operator << (std::ostream & out, variant const & _variant) // member, cause http://stackoverflow.com/questions/23355117/
	//{
	//	return _variant.apply_visitor(printer{out});
	//}

};

	struct printer
	{

		template< typename type >
		std::ostream &
		operator () (type const & _value) const
		{
			return out << _value;
		}

		std::ostream & out;

	};

template< typename first, typename ...rest >
std::ostream &
operator << (std::ostream & out, variant< first, rest... > const & _variant) // member, cause http://stackoverflow.com/questions/23355117/
{
	return _variant.apply_visitor(printer{out});
}

template< typename type >
struct is_variant
        : bool_< false >
{

};

template< typename first, typename ...rest >
struct is_variant< variant< first, rest... > >
        : bool_< true >
{

};

template< typename ...lhs_types, typename ...rhs_types >
void
swap(variant< lhs_types... > & _lhs, variant< rhs_types... > & _rhs) noexcept
{
    _lhs.swap(_rhs);
}

template< typename variant, typename ...arguments >
variant
make_variant(arguments &&... _arguments)
{
    return variant(std::forward< arguments >(_arguments)...);
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

} // namespace insituc
