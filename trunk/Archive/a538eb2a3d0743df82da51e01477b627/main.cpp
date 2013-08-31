

template<unsigned times_eight, unsigned>
struct get_type_by_length_impl
{
    using type = get_primitive_type<times_eight + 1>::type;
};

template<unsigned remainder>
struct get_type_by_length_impl<0, remainer>
{
    
};

struct 

struct get_type_by_length_impl<1, 0>
{
    using type = uint8_t;
};

struct get_type_by_length_impl<1, 0> { using type = uint8_t };

template<> struct get_type_by_length<2> { using type = uint8_t };
template<> struct get_type_by_length<3> { using type = uint8_t };

template<typename unsigned>
struct get_type_by_length : get_type_by_length_impl;

template<CRT, unsigned offset, unsigned length>
struct header_impl<offset, hlp_id_field<length> >
{
    using HLPType = get_type_with_length<length>::type;
    T getHLP() const
    {
        T result;
        memcpy(&result,
               &static_cast<CRT&>(*this).data[offset],
               sizeof(result));
        
    }
    
};

template<typename ...Args>
struct header : header_impl<header<Args...>, 0, Args...>
{
    enum {
        size = sum_size<Args...>::value;
    };
    typedef std::array<uint8_t, size> data;
};

template<unsigned BitCount> struct hlp_id_field {};
template<unsigned BitCount> struct array_field {};


using EthernerHeader = typename header<hlp_id_field<16>, array_field<6*8>, array_field<6*8> >::type;

int main()
{
    
}

    