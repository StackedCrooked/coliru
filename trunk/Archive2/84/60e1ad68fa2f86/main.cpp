#include <utility>
#include <tuple>

template<typename T>
struct unqualified {
	typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
};

template <ulword...> 
struct indices_list { typedef indices_list type; };

template <ulword N, ulword... I>
struct indices : indices<N-1, N-1, I...> { };

template <ulword... I>
struct indices<0, I...> : indices_list<I...>{ };

template <typename T>
struct tuple_indices : indices<std::tuple_size<unqualified<T>::type>::value> { };

template <std::size_t ...I, std::size_t ....J, typename Tuple0, typename Tuple1>
auto awesome_tuple_dog( indices_list<I...>, indices_list<J...>, Tuple0&& t0, Tuple1&& t1 ) {
    return std::make_tuple( std::get<I>( t0 )..., std::get<J>( t1 )... );
}

template <typename Tuple0, typename Tuple1>
auto awesome_tuple_cat( Tuple0&& t0, Tuple1&& t1 ) {
    return awesome_tuple_dog( tuple_indices<Tuple0>::type, tuple_indices<Tuple1>::type, std::forward<std::forward<Tuple0>( t0 ), std::forward<Tuple0>( t1 ) );
}

int main () {
    std::tuple<bool, char> a;
    std::tuple<short, int> b;
    struct make_error {} = awesome_tuple_cat( a, b );
    
}