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
     
    template <typename TStuff, typename TFinalTuple>
    auto awesome_tuple_dog( TStuff&&, TFinalTuple&& tuple ) {
    // A greater Tuple has been born..
    return std::forward<TFinalTuple>( tuple );
    }
     
    template <std::size_t ...I, std::size_t ...J, typename... Indices, typename Tuple0, typename Tuple1, typename... Tuplen>
    auto awesome_tuple_dog( stuff<indices_list<I...>, indices_list<J...>, Indices...>, Tuple0&& t0, Tuple1&& t1, Tuplen&&... tn ) {
    // We know for a fact that "stuff" has ever single indices list we need, but some of it is hidden
    // behind variadics. We need to unpack every single last one of the indices we need and get the 'I...' we need...
    return awesome_tuple_dog(
    stuff<Indices...>(), // deal with the next set of indices, and use them to unite the lesser tuples!
    std::make_tuple( std::get<I>( std::forward<Tuple0>( t0 ) )..., std::get<J>( std::forward<Tuple1>( t1 ) )... ),
    std::forward<Tuplen>( tn )... // keep going, consume the inferior tuples!
    );
    }
     
    template <typename... Tuplen>
    auto awesome_tuple_cat( Tuplen&&... tn ) {
    // It doens't cut it to just have tuple_indices<Tuplen>()..., because that's another variadic who's contents
    // are hard to get at in another function. Need to wrap it up in a 'stuff'
    //return awesome_tuple_dog( tuple_indices<Tuplen>()..., std::forward<Tuple0>( t0 ), std::forward<Tuple1>( t1 ) );
    return awesome_tuple_dog( stuff<typename tuple_indices<Tuplen>::type...>(), std::forward<Tuplen>( tn )... );
    }
     
    int main () {
    std::tuple<bool, char> a;
    std::tuple<short, int> b;
    struct {} _ = awesome_tuple_cat( a, b );
     
    }