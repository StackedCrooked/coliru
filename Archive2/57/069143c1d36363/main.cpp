#include <type_traits>
#include <vector>
#include <tuple>
#include <iostream>

template< std::size_t... Ns >
struct indices
{
    using next = indices< Ns..., sizeof...( Ns ) >;
};

template< std::size_t N >
struct make_indices
{
    using type = typename make_indices< N - 1 >::type::next;
};

template<>
struct make_indices< 0 >
{
    using type = indices<>;
};

template<typename T, typename U, std::size_t=0>
struct index {};

template<typename T, typename... Us, std::size_t N>
struct index<T,std::tuple<T,Us...>,N>
: std::integral_constant<std::size_t, N> {};

template<typename T, typename U, typename... Us, std::size_t N>
struct index<T,std::tuple<U,Us...>,N>
: index<T,std::tuple<Us...>,N+1> {};

template<typename T,typename I=void> struct unique;

template<typename... Ts>
struct unique< std::tuple<Ts...>, void >
: unique< std::tuple<Ts...>, typename make_indices<sizeof...(Ts)>::type >
{
};

template<typename... Ts, std::size_t... Is>
struct unique< std::tuple<Ts...>, indices<Is...> >
{
    using type = decltype( std::tuple_cat( std::declval<
        typename std::conditional<index<Ts,std::tuple<Ts...>>::value==Is,std::tuple<Ts>,std::tuple<>>::type
    >()... ) );
};

template<typename> struct vectorize;

template<typename... Ts>
struct vectorize<std::tuple<Ts...>>
{
    using type = std::tuple< std::vector<Ts>... >;
};

template<typename... Ts> class Store
{
    using Storage = typename vectorize<typename unique<std::tuple<Ts...>>::type>::type;
    Storage storage;
    
    template<typename T>
    decltype(std::get<index<T,typename unique<std::tuple<Ts...>>::type>::value>(storage))
    slot()
    {
        return std::get<index<T,typename unique<std::tuple<Ts...>>::type>::value>(storage);
    }

public:
    template<typename T> void add(T mValue) { 
        slot<T>().push_back(mValue); 
    }

    template<typename T> std::vector<T>& get() { 
        return slot<T>();
    }    
};

template<typename>
void dummy();

int main()
{
    std::cout << index<int, std::tuple<int, double, char>>::value << std::endl;
    std::cout << index<double, std::tuple<int, double, char>>::value << std::endl;
    std::cout << index<char, std::tuple<int, double, char>>::value << std::endl;
    //std::cout << index<float, std::tuple<int, double, char>>::value << std::endl;
    
    Store<int,int,double,int,double> store;
    store.add(42);
    store.add(3.1415);
    store.add(21);
    std::cout << store.get<int>().size() << std::endl; 
    std::cout << store.get<double>().size() << std::endl; 
}
