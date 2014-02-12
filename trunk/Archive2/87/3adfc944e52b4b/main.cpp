#pragma once
// Copyright (c) 2014 Alf P. Steinbach

#include <thisApp/support/cppx/Byte.h>      // cppx::Byte, cppx::bits_per_byte

#include <bitset>               // std::bitset
#include <initializer_list>     // std::initializer_list
#include <tuple>                // std::tuple, std::tuple_element

namespace cppx {
    using std::bitset;
    using std::initializer_list;
    using std::tuple;
    using std::tuple_element;

    template< class Value >
    class Small_set
    {
    private:
        static int constexpr bits_per_int = sizeof(int)*bits_per_byte;

        bitset<bits_per_int>    bits;

    public:
        auto contains( Value const v ) const
            -> bool
        { return bits[v]; }

        Small_set() {}

        Small_set( initializer_list<Value> const& values )
        {
            for( auto const v : values )
            {
                bits.set( v );
            }
        }
    };

    template< class... Values >
    auto small_set( Values const... values )
        -> Small_set< typename tuple_element<0, tuple< Values... > >::type >
    { return { values... }; }

}  // namespace cppx
