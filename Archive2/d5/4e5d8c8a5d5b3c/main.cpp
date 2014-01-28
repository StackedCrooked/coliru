#pragma once
#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <vector>
#include <deque>

#define CONSTEXPR_CTOR constexpr
#define CONSTEXPR      constexpr

namespace JSON
{
    template <typename Tag> struct Literal 
    { 
        bool operator==(Literal const&) const { return true;  } 
        bool operator< (Literal const&) const { return false; } 
    };

    typedef Literal<struct tag_undefined> Undefined;
    typedef Literal<struct tag_null>  Null;

    struct Object;
    struct Array;

    using Integer = int64_t;
    using Double  = long double;
    using String  = std::string;

    struct Bool { // circumvent (non-standard?) ambiguities initializing Value with MSVC12)
        explicit CONSTEXPR_CTOR Bool(bool value = false) : _value(value) {}
        Bool(Bool const&) = default;
        explicit operator bool() const { return _value; }

        friend bool operator< (Bool const& a, Bool const& b) { return a._value <  b._value;  }
        friend bool operator==(Bool const& a, Bool const& b) { return a._value == b._value;  }

    private:
        bool _value;
    } static CONSTEXPR True(true), False(false);

    typedef boost::variant<
            Undefined, // not legal as a JSON result
            Null, 
            Bool,
            boost::recursive_wrapper<Object>, 
            boost::recursive_wrapper<Array>,
            String,
            Integer,
            Double
        > Value;

    struct Object
    {
        using Entry = std::pair<String, Value>;
        using values_t = std::vector<Entry>; // TODO use a stable_vector?

        values_t values;

        Object() = default;
        explicit Object(std::initializer_list<values_t::value_type> init) : values(init) { }

        Value&       operator[](std::string const& key);
        Value const& operator[](std::string const& key) const;
        bool         has_key   (std::string const& key) const;

        bool operator==(Object const& o) const { return values == o.values; }

        friend values_t::const_iterator begin(Object const& a) { return std::begin(a.values); }
        friend values_t::const_iterator end  (Object const& a) { return std::end  (a.values); }
        friend values_t::      iterator begin(Object      & a) { return std::begin(a.values); }
        friend values_t::      iterator end  (Object      & a) { return std::end  (a.values); }
    };

    struct Array
    {
        typedef std::deque<Value> values_t;
        values_t values;

        Array() = default;
        /*explicit*/ Array(std::initializer_list<Value> values) : values(values) {}

        template <typename T> Value&       operator[](T&& key)       
            { return values.at(std::forward<T>(key)); }

        template <typename T> Value const& operator[](T&& key) const 
            { return values.at(std::forward<T>(key)); }

        bool operator==(Array const& o) const { return values == o.values; }

        friend values_t::const_iterator begin(Array const& a) { return std::begin(a.values); }
        friend values_t::const_iterator end  (Array const& a) { return std::end  (a.values); }
        friend values_t::      iterator begin(Array      & a) { return std::begin(a.values); }
        friend values_t::      iterator end  (Array      & a) { return std::end  (a.values); }
    };

    static inline Array&         as_array   (Value& v)       { return boost::get<Array>(v);   }
    static inline Object&        as_object  (Value& v)       { return boost::get<Object>(v);  }
    static inline String&        as_string  (Value& v)       { return boost::get<String>(v);  }
    static inline Bool&          as_boolean (Value& v)       { return boost::get<Bool>(v);    }
    static inline Double&        as_double  (Value& v)       { return boost::get<Double>(v);  }
    static inline Integer&       as_int64   (Value& v)       { return boost::get<Integer>(v); }
    static inline Array   const& as_array   (Value const& v) { return boost::get<Array>(v);   }
    static inline Object  const& as_object  (Value const& v) { return boost::get<Object>(v);  }
    static inline String  const& as_string  (Value const& v) { return boost::get<String>(v);  }
    static inline Bool    const& as_boolean (Value const& v) { return boost::get<Bool>(v);    }
    static inline Double  const& as_double  (Value const& v) { return boost::get<Double>(v);  }
    static inline Integer const& as_int64   (Value const& v) { return boost::get<Integer>(v); }

    // standard char streams are assumed to be utf8
    Value readFrom(std::istream&);
    Value readFrom(std::istream&&);

    Value parse(std::string const&);
    std::string to_string(Value const&);

    std::ostream&  operator<<(std::ostream&,  Value const&);
}