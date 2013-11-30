#include <utility>
#include <tuple>

template <typename T>
struct unqualified { typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type; };
template <typename... T>
struct stuff{ typedef stuff type;/* contains all the types! */ };
template <std::size_t...> 
struct indices_list { typedef indices_list type; };
template <std::size_t N, std::size_t... I>
struct indices : public indices<N-1, N-1, I...> { };
template <std::size_t... I>
struct indices<0, I...> : public indices_list<I...>{ };
template <typename T>
struct tuple_indices : public indices<std::tuple_size<typename unqualified<T>::type>::value> { };

template <typename TStuff>
auto awesome_tuple_dog( TStuff&& ) {
	return std::tuple<>{};
}
template <typename TStuff, typename TFinalTuple>
auto awesome_tuple_dog( TStuff&&, TFinalTuple&& tuple ) {
	return std::forward<TFinalTuple>( tuple );
}
template <std::size_t ...I, std::size_t ...J, typename... Indices, typename Tuple0, typename Tuple1, typename... Tuplen>
auto awesome_tuple_dog( stuff<indices_list<I...>, indices_list<J...>, Indices...>, Tuple0&& t0, Tuple1&& t1, Tuplen&&... tn ) {
    return awesome_tuple_dog( stuff<indices_list<J..., (I + sizeof...(J))...>, Indices...>(),
        std::make_tuple( std::get<I>( std::forward<Tuple0>( t0 ) )..., std::get<J>( std::forward<Tuple1>( t1 ) )... ), std::forward<Tuplen>( tn )...  );
}

template <typename... Tuplen>
auto awesome_tuple_cat( Tuplen&&... tn ) {
    return awesome_tuple_dog( stuff<typename tuple_indices<Tuplen>::type...>(), std::forward<Tuplen>( tn )... );
}

int main () {
    std::tuple<bool, char> a;
    std::tuple<short, int> b;
    std::tuple<long long> c;
    struct {} _ = awesome_tuple_cat( );
    struct {} __ = awesome_tuple_cat( a, b );
    struct {} ___ = awesome_tuple_cat( a, b, c );
    
}