#include <iostream>
#include <utility>
#include <type_traits>
#include <tuple>

void tits ( int tit, int titties, int tittays ) {
    std::cout << tit;
    std::cout << ' ';
    std::cout << titties;
    std::cout << ' ';
    std::cout << tittays;
    std::cout << ' ';
}

template <typename ...Ts>
void ForwardToTits ( std::tuple<Ts...> t ) {
    // Impossible because an individual Tuple
    // with an individual 'get'
    // and a parameter type cannot be used to
    // determine the order of the parameters in
    // the first place, and so a sequence
    // has to be generated
    // (we could also keep indexing information on variadic parameter packs)
    // (because that would be useful. Incredibly useful)
    // (but why do that when we can break implementers backs? :3c)
    tits( std::get<Ts>( t )... );
}

int main ( int argc, char** argv ) {
	auto t = std::make_tuple( 1, 2, 3 );
	ForwardToTits( t );

}