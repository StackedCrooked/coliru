#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>

struct A {}; struct B {}; struct C {}; struct D {}; struct E {};
struct F { F() { std::cout << "F::constructor\n"; } };
struct G {}; struct H {};

int main()
{
    using namespace boost::mpl ;
    using my_map = map< pair< A, map< pair< B, map< pair< C, vector<E,G,H,F> > > > > >,
                        pair< int_<32>, map< pair< C, vector<E,F,G>   > > >
                      >;
    at< at< at< at< my_map, A >::type, B >::type, C >::type, int_<3> >::type{} ;
    at< at< at< my_map, int_<32> >::type, C >::type, int_<1> >::type{} ;
}
