#include <utility>
#include <tuple>

template <std::size_t I, std::size_t J> struct idxij { };
template <typename... T> struct stuff { typedef stuff type; };
template <typename TBin, std::size_t I, std::size_t J, std::size_t... Sizen>
struct idx : public TBin { typedef TBin type; /* keep a catalog of all our previous types */ /* Useful later for function-signature template type deduction with 'stuff' */ };
template <typename... TBinn, std::size_t I, std::size_t J, std::size_t ... Sizen> // No N here, just the rest of the sizes
struct idx<stuff<TBinn...>, I, J, 0, Sizen...> : public idx<stuff<TBinn...>, I + 1, 0, Sizen...>{ }; // Terminal Specialization; don't forget to +1 here on I to go to next iteration of I
template <typename... TBinn, std::size_t I, std::size_t J, std::size_t N, std::size_t ... Sizen> // N is the number of times to inherit to add to TBinn bin
struct idx<stuff<TBinn...>, I, J, N, Sizen...> : public idx<stuff<TBinn..., idxij<I, J>>, I, J + 1, N - 1, Sizen...>{ }; //Generic case to inherit to terminal specialization: store pairs in stuff

template <std::size_t... I, std::size_t... J, typename TTuple>
auto awesome_tuple_dog( stuff<idxij<I, J>...>, TTuple&& master ) { // Variable amount of indices, one for each tuple
    return std::make_tuple( std::get<J>( std::get<I>( std::forward<TTuple>( master ) ) )... );
}
template <typename... Tuplen>
auto awesome_tuple_cat( Tuplen&&... tn ) {
	return awesome_tuple_dog( idx<stuff<>, 0, 0, std::tuple_size<typename std::decay<Tuplen>::type>::value...>( ), std::forward_as_tuple( tn... ) ); // Get the size of each tuple, pass it through; must use ::type on idx because `TBin` and `TBinn` end up being a long `stuff` expression
}

int main () {
    // Should produce 4 idxij for 0 to 3 inclusive, then 2 idxij for 0 to 1 inclusive 
    // don't forget to start it off with an empty list of stuff<> otherwise it'll
    // immediately traverse to base case and fuck the day up
    // struct {} g_ = idx<stuff<>, 0, 0, 4, 2>::type();
    std::tuple<bool, char> a;
    std::tuple<short, int> b;
    std::tuple<long long> c;
    struct {} _ = awesome_tuple_cat( );
    struct {} __ = awesome_tuple_cat( a, b );
    struct {} ___ = awesome_tuple_cat( a, b, c );
    
}