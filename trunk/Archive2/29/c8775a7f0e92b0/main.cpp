#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>

struct A {}; struct B {}; struct C {}; struct D {}; struct E {};
struct F { F() { std::cout << "F::constructor\n"; } };
struct G {};

int main()
{
    using namespace boost::mpl ;
    using my_map = map< pair< A, map< pair< B, map< pair< C, vector<C,D,E,F> > > > > >,
                        pair< B, map< pair< C, vector<E,F,G>   > > >
                      >;
    at< at< at< at< my_map, A >::type, B >::type, C >::type, int_<3> >::type{} ;
    at< at< at< my_map, B >::type, C >::type, int_<1> >::type{} ;
}
