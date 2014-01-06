#include <tuple>

template<class T>
struct flatten;

template< template<class...> class TT, class... Ts >
struct flatten< TT<Ts...> >
{
    template<class...>
    struct join {};
    
    template<class... L, class... R, class... Rest>
    struct join< TT<L...>, TT<R...>, Rest... >
    {
        using type = typename join< TT<L..., R...>, Rest... >::type;
    };
    
    template<class... M>
    struct join< TT<M...> >
    {
        using type = TT<M...>;
    };
    
    template<class T>
    struct flatten_impl
    {
        using type = TT<T>;
    };
    template<class... L, class... Rest>
    struct flatten_impl< TT<TT<L...>, Rest...> >
    {
        using type = typename join< typename flatten_impl<L>::type..., typename flatten_impl<Rest>::type... >::type;
    };
    template<class... L>
    struct flatten_impl< TT<L...> >
    {
        using type = typename join< typename flatten_impl<L>::type... >::type;
    };
    
    using type = typename join< typename flatten_impl<Ts>::type... >::type;
};

#include <iostream>
template<class T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main(){
    typedef std::tuple<int,std::tuple<std::tuple<std::tuple<int,long>>>,int> tup;
    //static_assert(std::is_same<typename flatten<tup>::type,std::tuple<int,int,long,int> >::value,"");
    print_type<flatten<tup>::type>();
}