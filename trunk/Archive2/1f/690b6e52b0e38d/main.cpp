// Heterogeneous vector (unordered) over specified sequence of types

#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/container/map.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace boost;

template<typename ...Ts>
struct static_poly_seq
{
    typename fusion::result_of::as_map
    <
        typename mpl::transform
        <
            mpl::vector<Ts...>,
            fusion::pair< mpl::_1, std::vector<mpl::_1> >
        >::type 
    >::type vectors;
};

template<typename ...Types, typename T>
void push_back_2D(static_poly_seq<Types...> &seq, const T &value)
{
    fusion::at_key<T>(seq.vectors).push_back(value);
}

template<typename ...Types, typename PolymorhicUnaryFunctor>
void for_each_2D(static_poly_seq<Types...> &seq, PolymorhicUnaryFunctor f)
{
    fusion::for_each(seq.vectors, [=](auto &xs)
    {
        for(auto &x : xs.second)
            f(x);
    });
}
/***************************************************************/
int main()
{
    static_poly_seq<int, double> seq;

    for(int i=0; i!=3; ++i)
    {
        push_back_2D(seq, i);
        push_back_2D(seq, i+0.1);
    }

    for_each_2D(seq, [](auto x)
    {
        cout << x << endl;
    });
}
