#include<tuple>
#include<iostream>

template<typename ... Args>
struct SwitchMap
{
    static const size_t ArgsSize = sizeof ... (Args); 
    using ArgsTuple = std::tuple<Args ...>;
    using InType = typename std::tuple_element<0,ArgsTuple>::type;
    using OutType = typename std::tuple_element<1,ArgsTuple>::type;

    std::tuple<Args ...> t;
    SwitchMap(Args const& ... args) : t(std::make_tuple(args ...))
    {
        static_assert((ArgsSize & 1) &&  (ArgsSize > 2), " ");
    }
    
    template<int> struct int2type{};
    
    template<int N>
    OutType get(InType const& in, int2type<N>) const
    {
        return in == std::get<N>(t) ? std::get<N+1>(t) : get(in,int2type<N+2>());
    }

    OutType get(InType const& in, int2type<ArgsSize-1>) const
    {
        return std::get<ArgsSize-1>(t);
    }

    OutType operator[](InType const& in) const
    {
        return get(in,int2type<0>());
    }

};


template<typename ... Args>
auto makeSwitchMap(Args const& ... args)
{
    return SwitchMap<Args ...>(args ...);    
}


int main()
{
    auto switchMap = makeSwitchMap(1,std::string("Say Hi"),2,std::string("Say Goodbye"),std::string("Say nothing"));
    std::cout<<switchMap[1]<<std::endl;
    std::cout<<switchMap[2]<<std::endl;
    std::cout<<switchMap[4]<<std::endl;
}
