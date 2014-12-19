#include<tuple>
#include<iostream>

template<typename ... Args>
struct SwitchMap
{
    using InType = typename std::tuple_element<std::tuple<Args...> >::type;
    
    std::tuple<Args ...> t;
    SwitchMap(Args const& ... args) : t(std::make_tuple(args ...))
    {
        static_assert((sizeof ... (Args) & 1) && (sizeof ... (Args) > 2), "wrong input size");
        //possibly add another check for consistency of In and Out types
    }
    
    template<int> struct int2type{};
    
    template<int N>
    auto get(InType const& in, int2type<N>) const
    {
        return in == std::get<N>(t) ? std::get<N+1>(t) : get(in,int2type<N+2>());
    }

    auto get(InType const& in, int2type<ArgsSize-1>) const
    {
        return std::get<ArgsSize-1>(t);
    }

    auto operator[](InType const& in) const
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
