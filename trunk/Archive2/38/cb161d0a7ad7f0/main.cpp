#include <utility>
#include <tuple>

template <std::size_t I, std::size_t J> struct idxij { };
template <typename... T> struct stuff { typedef stuff type; };
template <typename TBin, std::size_t I, std::size_t J, std::size_t... Sizen>
struct idx { typedef TBin type; /* keep a catalog of all our previous types */ /* Useful later for function-signature template type deduction with 'stuff' */ };
template <typename... TBinn, std::size_t I, std::size_t J, std::size_t ... Sizen>
struct idx<stuff<TBinn...>, I, J, 0, Sizen...> : public idx<stuff<TBinn...>, I, 0, Sizen...> {  }; // Terminal Specialization
template <typename... TBinn, std::size_t I, std::size_t J, std::size_t N, std::size_t ... Sizen> // N is the number of times to inherit to add to TBinn bin
struct idx<stuff<TBinn...>, I, J, N, Sizen...> : public idx<stuff<TBinn..., idxij<I, J>>, I, J+1, N-1, Sizen...> {  }; //Generic case to inherit to terminal specialization: store pairs in stuff

/*template <std::size_t... I, typename... Tuplen>
auto awesome_tuple_dog( indices<I...>, TTuple&& master ) {
    return std::make_tuple( std::get<I>( std::forward<TTuple>( master ) )... );
}

template <typename... Tuplen>
auto awesome_tuple_cat( Tuplen&&... tn ) {
    typedef std::tuple<Tuplen...> master_tuple;
    typedef stuff<typename tuple_indices<Tuplen>::type...>();
    return awesome_tuple_dog( tuple_indices<master_tuple>(), std::make_tuple( std::forward<Tuplen>( tn ) ) );
}*/

int main () {
    // Should produce 4 idxij for 0 to 3 inclusive, then 2 idxij for 0 to 1 inclusive 
    // don't forget to start it off with an empty list of stuff<> otherwise it'll
    // immediately traverse to base case and fuck the day up
    struct {} g_ = idx<stuff<>, 0, 0, 4, 2>::type();
    //std::tuple<bool, char> a;
    //std::tuple<short, int> b;
    //std::tuple<long long> c;
    //struct {} _ = awesome_tuple_cat( );
    //struct {} __ = awesome_tuple_cat( a, b );
    //struct {} ___ = awesome_tuple_cat( a, b, c );
    
}