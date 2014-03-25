#include <iostream>
#include <tuple>

template<unsigned int N>
struct A {
    unsigned int getN() const { return N; }
    void dostuff() const { std::cout << N << " "; }
};

auto globals = std::make_tuple( A<3>{}, A<7>{}, A<10>{}, A<200>{} );

template <int idx> void run( int v );
template <>        void run<std::tuple_size<decltype(globals)>::value>( int ) {}
template <int idx = 0> void run( int v ) {
    auto & a = std::get<idx>(globals);
    if ( v < a.getN() ) {
        a.dostuff();
    } else {
        run<idx+1>(v);
    }
}

int main() {
    for( int i = 0; i<20; ++i)
        run( i );
}
