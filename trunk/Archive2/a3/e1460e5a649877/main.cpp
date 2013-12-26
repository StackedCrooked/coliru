// Heterogeneous vector (unordered) over specified sequence of types

#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/container/map.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/phoenix/stl/algorithm.hpp>
#include <boost/phoenix.hpp>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using namespace boost;
using namespace std;
using phoenix::arg_names::arg1;

// ___________________________________________________________________ //
// syntax sugar
struct get_fusion_pair_value
{
    template<typename FusionPair>
    auto operator()(FusionPair &fp) const -> decltype(fp.second)
    {
        return fp.second;
    }
};
BOOST_PHOENIX_ADAPT_CALLABLE(fp_second, get_fusion_pair_value, 1)
// ___________________________________________________________________ //

template<typename ...Ts>
struct poly_seq
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

template<typename ...Ts, typename T>
void push_back(poly_seq<Ts...> &seq, const T &value)
{
    fusion::at_key<T>(seq.vectors).push_back(value);
}

template<typename ...Ts, typename PolymorhicUnaryFunctor>
void for_each(poly_seq<Ts...> &seq, PolymorhicUnaryFunctor f)
{
    fusion::for_each
    (
        seq.vectors,
        phoenix::for_each(fp_second(arg1), f)
    );
}
// ___________________________________________________________________ //

struct Print
{
    template<typename T>
    void operator()(const T &x)
    {
        cout << x << endl;
    }
};

int main()
{
    poly_seq<int, double> seq;

    for(int i=0; i!=3; ++i)
    {
        push_back(seq, i);
        push_back(seq, i+0.1);
    }

    for_each(seq, Print{});
}
