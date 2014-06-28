#include <iostream>
#include <string>
#include <vector>
#include <tuple>

namespace client
{
    template<typename... Args>
    struct tuple;
    
    template<typename Head, typename... Tail>
    struct tuple<Head, Tail...> : tuple<Tail...>
    {
        tuple(Head h, Tail... tail)
            : tuple<Tail...>(tail...), head_(h)
        {}
        typedef tuple<Tail...> base_type;
        typedef Head           value_type;
        
        base_type& base = static_cast<base_type&>(*this);
        Head       head_;
    };
    
    template<>
    struct tuple<>
    {};
    
    template<int I, typename Head, typename... Args>
    struct getter
    {
        typedef typename getter<I-1, Args...>::return_type return_type;
        static return_type get(tuple<Head, Args...> t)
        {
            return getter<I-1, Args...>::get(t);
        }
    };
    
    template<typename Head, typename... Args>
    struct getter<0, Head, Args...>
    {
        typedef typename tuple<Head, Args...>::value_type return_type;
        static return_type get(tuple<Head, Args...> t)
        {
            return t.head_;
        }
    };
    
    template<int I, typename Head, typename... Args>
    typename getter<I, Head, Args...>::return_type
    get(tuple<Head, Args...> t)
    {
        return getter<I, Head, Args...>::get(t);
    }
    
    template<int...>
    struct seq {};
    
    template<int N, int... S>
    struct gens : gens<N-1, N-1, S...> {};

}

int foo(int i, double d)
{
    std::cout << "foo: " << i << " " << d << std::endl;
    return i;
}
    
template<typename F, typename Tuple, bool GotArgs, int Total, int... N>
struct call_impl
{
    auto static call(F f, Tuple&& t)
    {
        return call_impl<F, Tuple, Total == 1 + sizeof...(N), 
                                   Total, N..., sizeof...(N)
                        >::call(f, std::forward<Tuple>(t));
    }
};

template<typename F, typename Tuple, int Total, int... N>
struct call_impl<F, Tuple, true, Total, N...>
{
    auto static call(F f, Tuple&& t)
    {
        return f(std::get<N>(std::forward<Tuple>(t))...);
    }
};


template<typename F, typename Tuple>
auto call(F f, Tuple&& t)
{
    typedef typename std::decay<Tuple>::type type;
    return call_impl<F, Tuple, 0 == std::tuple_size<type>::value, 
                                    std::tuple_size<type>::value
                    >::call(f, std::forward<Tuple>(t));
}

int main()
{
    client::tuple<int, double> t(12, 2.34);
    std::cout << client::get<0>(t) << " " << client::get<1>(t) << std::endl;
    
    std::tuple<int, double> t1(1, 2.3);
    std::cout << call(foo, t1) << std::endl;
}
