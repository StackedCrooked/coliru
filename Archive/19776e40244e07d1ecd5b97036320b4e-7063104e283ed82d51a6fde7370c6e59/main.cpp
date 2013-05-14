#include <iostream>
#include <utility>
#include <type_traits>
#include <tuple>

struct disambiguator_t {};
const auto split = disambiguator_t();

template<unsigned...> struct compiler_indices{};

template<unsigned N, unsigned... Is>
struct compiler_indices_gen : compiler_indices_gen<N-1, N-1, Is...>{};

template<unsigned... Is>
struct compiler_indices_gen<0, Is...> : compiler_indices<Is...>{};

template <typename TCondition, typename T = void>
struct enable {

	typedef typename std::enable_if<!TCondition::value, T>::type type;

};

template <typename TCondition, typename T = void>
struct disable {

	typedef typename std::enable_if<TCondition::value, T>::type type;

};

template <std::size_t n>
void Print ( ) {

}

template <std::size_t n, typename T, typename ...Tn>
void Print ( T&& arg, Tn&&... argn ) {
    std::cout << arg << ' ';
	Print<n - 1, Tn...>( std::forward<Tn>( argn )... );
}

template<typename... Ts, typename... Vs>
void cleave(Ts&&... ts, disambiguator_t const&, Vs&&... vs){
	//Print<sizeof...(Ts)>( std::forward<Ts>( ts )... );

	std::cout << std::endl << "Split!" << std::endl;

	//Print<sizeof...(Vs)>( std::forward<Vs>( vs )... );
}

template<typename... Ts, typename U, typename... Vs, typename disable<typename std::is_same<typename std::decay<U>::type, disambiguator_t>, int>::type = 0>
void cleave(Ts&&... ts, U&& u, Vs&&... vs){
	cleave<Ts..., U>(std::forward<Ts>(ts)..., std::forward<U>(u), std::forward<Vs>(vs)...);
}

template<typename... Ts, typename... Vs, unsigned... I>
void cleave_tuple( compiler_indices<I...>, std::tuple<Ts...> ts, Vs&&... vs ){
	cleave<Ts..., const disambiguator_t&>( std::forward<Ts>( std::get<I>( ts ) )..., split, std::forward<Vs>(vs)...);
}

template<typename... Ts, typename... Vs>
void cleave( std::tuple<Ts...> ts, Vs&&... vs ){
	typedef compiler_indices_gen<sizeof...( Ts )> indices;
	typedef std::tuple<Ts...> tuple_type;

	cleave_tuple( indices(), std::forward<tuple_type>( ts ), std::forward<Vs>(vs)...);
}

int main ( int argc, char** argv ) {
	auto t = std::make_tuple( 1, 2, 3, 7 );
	cleave( t, 4, 5, 6 );

}