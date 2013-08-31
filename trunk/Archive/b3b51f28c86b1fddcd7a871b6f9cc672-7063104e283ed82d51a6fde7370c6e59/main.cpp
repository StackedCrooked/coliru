#include <iostream>
#include <utility>

struct disambiguator_t {};
const auto split = disambiguator_t();

template <typename ...Tn>
void Print ( Tn&&... argn ) {
    using swallow = int[];
    (void)swallow{ (std::cout << argn << " ", 0)... };
}

#include <type_traits>

template<class C, class T = int>
using DisableIf = typename std::enable_if<!C::value, T>::type;

template<class... Ts, class... Vs>
void cleave(Ts&&... ts, disambiguator_t const&, Vs&&... vs){
    Print( std::forward<Ts>( ts )... );
    
    std::cout << std::endl << "Split!" << std::endl;
    
    Print( std::forward<Vs>( vs )... );
}

template<class... Ts, class U, class... Vs, DisableIf<std::is_same<U, disambiguator_t const&>> = 0>
void cleave(Ts&&... ts, U&& u, Vs&&... vs){
    cleave<Ts..., U>(std::forward<Ts>(ts)..., std::forward<U>(u), std::forward<Vs>(vs)...);
}

int main ( int argc, char** argv ) {
    cleave( 1, 2, 3, split, 4, 5, 6 );
    
}