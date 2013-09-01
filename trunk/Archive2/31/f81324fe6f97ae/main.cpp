#include <iostream>
#include <bitset>

template < typename CRTP, typename UT >
struct enum_class
{
    using underlying_type = UT;
    
    friend constexpr CRTP operator&(CRTP const& p0, CRTP const& p1)
    {
        return CRTP(p0.m & p1.m);
    }
    friend constexpr CRTP operator|(CRTP const& p0, CRTP const& p1)
    {
        return CRTP(p0.m | p1.m);
    }
    friend constexpr CRTP operator^(CRTP const& p0, CRTP const& p1)
    {
        return CRTP(p0.m ^ p1.m);
    }
    
    constexpr explicit enum_class(underlying_type p)
        : m(p)
    {}
    // could have a virtual dtor
    
    constexpr explicit operator underlying_type() const
    {
        return m;
    }
    
private:
    friend struct enum_class;
    underlying_type m;
};

struct my_enum : enum_class < my_enum, unsigned char >
{
    enum : underlying_type
    {
          A = 1<<0
        , B = 1<<1
        , C = 1<<2
    };
    
    using enum_class::enum_class;
};


int main()
{
    my_enum m0(my_enum::A);
    my_enum m1(my_enum::B);
    std::cout << "hello: " << (int)my_enum::underlying_type(m0 | m1) << std::endl;
}
