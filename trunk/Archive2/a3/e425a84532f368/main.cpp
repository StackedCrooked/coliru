// TYPE ARRAY BELOW
template<typename... Types>
struct type_array;

template<>
struct type_array<>
{
};

template<typename Head, typename... Tail>
struct type_array<Head, Tail...> : private type_array<Tail...> 
{
    typedef type_array<Tail...> cdr;
    typedef Head car;
};

template<int Index, typename Tuple>
struct type_array_element;

template<int Index, typename Head, typename... Tail>
struct type_array_element<Index, type_array<Head, Tail...>>
{
    typedef typename type_array_element<Index-1, type_array<Tail...> >::type type;
};

template<typename Head, typename... Tail>
struct type_array_element<0, type_array<Head, Tail...>> 
{
    typedef Head type;
};

template<int Index, typename Tuple>
struct type_array_get;

template<int Index, typename Head, typename... Tail>
struct type_array_get<Index, type_array<Head, Tail...>> 
{
    typedef typename type_array_element<Index-1, type_array<Tail...>>::type type;
};

template<typename... Types>
struct type_array_size;

template<>
struct type_array_size<type_array<>>
{
    static const unsigned size = 0;
};

template<typename Head, typename... Tail>
struct type_array_size<type_array<Head, Tail...>> 
{
    static const unsigned size = 1 + type_array_size<type_array<Tail...>>::size;
};

// STORE BELOW
#include <cstdint>

template<int Bits>
struct BitStore
{
    // Static asserts
    static_assert(Bits % 8 == 0, "Invalid BitStore size, must be multiple of 8");
    static_assert(Bits < 32, "Invalid BitStore size, must be at most equal to 32bits");
};

template<>
struct BitStore<8>
{
    typedef uint8_t type;
};

template<>
struct BitStore<16>
{
    typedef uint16_t type;
};

template<>
struct BitStore<32>
{
    typedef uint32_t type;
};

// SUM BELOW
template<int... N>
struct SUM;

template<>
struct SUM<>
{
    static const int sum = 0;
};

template<int val, int... N>
struct SUM<val, N...>
{
    static const int sum = val + SUM<N...>::sum;
};

// Int Sequence BELOW
template<int Index, int... S>
struct get_integer;

template<int val, int... S>
struct get_integer<0, val, S...>
{
    static const unsigned value = val;
};

template<int Index, int val, int... S>
struct get_integer<Index, val, S...>
{
    static const unsigned value = get_integer<Index-1, S...>::value;
};

// BITSET BELOW
#include <array>

template<typename type_array, int... N>
class Bitfield
{   
    static_assert(sizeof...(N) == type_array_size<type_array>::size, "type array / bits - length mismatch");
    
    public:
        typedef type_array types;
        
        static const unsigned max_index = sizeof...(N);
        // Assert none of the int... N's are negative
        static const int total_num_bits = SUM<N...>::sum;
        typedef typename BitStore<total_num_bits>::type store_type;
    
    public:
        // TODO: Static assert that all 1 sized fields are bools
        constexpr Bitfield(store_type init_value = store_type())
        : store(init_value)
        {
        }
       
        store_type store;
};

template<int Index, typename... Types, int... S>
constexpr int bitfield_size(const Bitfield<type_array<Types...>, S...>&)
{
    return get_integer<Index, S...>::value;
}

template<int Index, int val, int... S>
struct bitfield_offset_struct
{
    static const int value = get_integer<Index, val, S...>::value + bitfield_offset_struct<Index-1, val, S...>::value;
};

template<int val, int... S>
struct bitfield_offset_struct<0, val, S...>
{
    static const int value = get_integer<0, val, S...>::value;
};

template<int Index, typename... Types, int... S>
constexpr int bitfield_offset(const Bitfield<type_array<Types...>, S...>&)
{
    return bitfield_offset_struct<Index, S...>::value - get_integer<Index, S...>::value;
}

template<int Index, int Initial_Index = Index, typename... Types, int... S>
unsigned get(const Bitfield<type_array<Types...>, S...>& t)
{
    static_assert(Initial_Index <= t.max_index, "invalid bitfield get access");
    static_assert(bitfield_offset<Initial_Index>(t) <= t.total_num_bits, "invalid get implementation");
    
    if(Index == 0)
    {
        if(bitfield_size<Initial_Index>(t) == 1)
        {
            return (t.store & (1 << bitfield_offset<Initial_Index>(t))) != 0;
        }
        else
        {
            return (t.store >> bitfield_offset<Initial_Index>(t)) & ((1 << bitfield_size<Initial_Index>(t)) - 1);
        }
    }
    else
    {
        return get<Index ? Index-1 : 0, Initial_Index>(t);
    }
}

#include <iostream>
#include <bitset>
template<int Index, int Initial_Index = Index, typename... Types, int... S>
void set_raw(Bitfield<type_array<Types...>, S...>& t, unsigned argument)
{
    static_assert(Initial_Index <= t.max_index, "invalid bitfield get access");
    if(Index == 0)
    {
        int bitmask = ((1 << bitfield_size<Initial_Index>(t)) - 1) << bitfield_offset<Initial_Index>(t);
        t.store = (t.store  & ~bitmask)
                | (argument &  bitmask);
    }
    else
    {
        set_raw<Index ? Index-1 : 0, Initial_Index>(t, argument);
    }
}

template<int Index, int Initial_Index = Index, typename... Types, int... S>
void set(Bitfield<type_array<Types...>, S...>& t, unsigned argument)
{
    set_raw<Index>(t, argument << bitfield_offset<Initial_Index>(t));
}

#include <iostream>
#include <typeinfo>

int main()
{
    typedef type_array<int, float, std::string> types;
    typedef type_array_get<1, types>::type floating;
    static_assert(std::is_same<floating, float>::value, "broken type_array_get");
    
    // TODO: Fix issue, with getting the int type out
    //static_assert(std::is_same<type_array_get<0, types>::type, int>::value, "broken type_array_get");
    static_assert(std::is_same<type_array_get<1, types>::type, float>::value, "broken type_array_get");
    static_assert(std::is_same<type_array_get<2, types>::type, std::string>::value, "broken type_array_get");
    
    static_assert(std::is_same<BitStore<8>::type, uint8_t>::value, "broken bitstore");
    static_assert(std::is_same<BitStore<16>::type, uint16_t>::value, "broken bitstore");
    static_assert(std::is_same<BitStore<32>::type, uint32_t>::value, "broken bitstore");
    
    typedef type_array<bool, unsigned, unsigned> bitfield_types;
    auto b = Bitfield<bitfield_types, 1, 5, 10>(0xFFFF);
    
    static_assert(bitfield_size<0>(b) == 1, "bitfield_size_broken");
    static_assert(bitfield_size<1>(b) == 5, "bitfield_size_broken");
    static_assert(bitfield_size<2>(b) == 10, "bitfield_size_broken");
    
    std::cout << get<0>(b) << std::endl;
    set<0>(b,0);
    std::cout << get<0>(b) << std::endl;
    std::cout << get<1>(b) << std::endl;
    set<1>(b,0);
    std::cout << get<1>(b) << std::endl;
    std::cout << get<2>(b) << std::endl;
    set<2>(b,0);
    std::cout << get<2>(b) << std::endl;
    set<2>(b,1);
    std::cout << get<2>(b) << std::endl;
    
    /*
    typedef type_array<bool, bool, bool, bool, bool, bool, unsigned> bitfield_types;
    auto b = Bitfield<bitfield_types, 1, 1, 1, 1, 1, 1, 2>(0b11000000);
    
    std::cout << get<0>(b);
    std::cout << get<1>(b);
    std::cout << get<2>(b);
    std::cout << get<3>(b);
    std::cout << get<4>(b);
    std::cout << get<5>(b);
    std::cout << std::endl;
    
    std::cout << get<6>(b);
    */
}