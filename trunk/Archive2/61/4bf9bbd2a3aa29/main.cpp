#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/or.hpp>
#include <boost/array.hpp>

using namespace boost;

template< typename AdjacencyList, typename Key, typename Default = mpl::set<> >
struct at_default
{
    typedef typename mpl::eval_if
    <
        mpl::has_key<AdjacencyList, Key>,
        mpl::at<AdjacencyList, Key>,
        mpl::identity<Default>
    >::type type;
};

template
<
    typename AdjacencyList,
    typename From, typename To,
    typename Queue = mpl::deque<From>,
    typename Visited = mpl::set<>
>
struct has_path
{
    typedef typename mpl::front<Queue>::type head;
    typedef typename at_default<AdjacencyList, head>::type adjacent;
    
    typedef mpl::filter_view
    <
        adjacent,
        mpl::not_< mpl::has_key<Visited, mpl::_1> >
    > not_visited_adjacent;

    typedef typename mpl::copy
    <
        not_visited_adjacent,
        mpl::inserter<typename mpl::insert<Visited, head>::type, mpl::_1>
    >::type new_visited;

    typedef typename mpl::copy
    <
        not_visited_adjacent,
        mpl::back_inserter<typename mpl::pop_front<Queue>::type>
    >::type new_queue;
    
    typedef typename mpl::or_
    <
        mpl::has_key<adjacent, To>,
        typename mpl::eval_if
        <
            mpl::empty<new_queue>,
            mpl::identity< mpl::bool_<false> >,
            has_path<AdjacencyList, From, To, new_queue, new_visited>
        >::type
    >::type type;
};

template
<
    typename AdjacencyList,
    typename From, typename To
>
struct insert_directed_edge
{
    typedef typename mpl::insert
    <
        typename mpl::erase_key<AdjacencyList, From>::type,
        mpl::pair
        <
            From,
            typename mpl::insert
            <
                typename at_default<AdjacencyList, From>::type,
                To
            >::type
        >
    >::type type;
};

namespace test_adjacency_list
{
     typedef mpl::map
    <
        mpl::pair< int, mpl::set<double> >,
        mpl::pair< double, mpl::set<char, unsigned> >,
        mpl::pair< unsigned, mpl::set<float> >
    > AdjacencyList;

    BOOST_MPL_ASSERT((has_path<AdjacencyList, int, double>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, int, char>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, int, unsigned>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, int, float>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, double, char>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, double, unsigned>));
    BOOST_MPL_ASSERT((has_path<AdjacencyList, double, float>));
    BOOST_MPL_ASSERT((mpl::not_< has_path<AdjacencyList, double, int> >));
    BOOST_MPL_ASSERT((mpl::not_< has_path<AdjacencyList, char, int> >));
    
    typedef insert_directed_edge<AdjacencyList, double, void>::type Extended;
    BOOST_MPL_ASSERT((has_path<Extended, int, void>));
    BOOST_MPL_ASSERT((mpl::not_< has_path<AdjacencyList, int, void*> >));
}

/***********************************************************/

#include <iostream>
#include <utility>

struct Stop{};
template<unsigned n, unsigned i=n, unsigned j=i-1>
struct quadratic_recursion
{
    enum{ inner = n-j, outter = n-i };
    
    template<typename F>
    void operator()(F f)
    {
        f.template operator()<outter, inner>
        (
            quadratic_recursion<n, i, j-1>()
        );
    }
};

template<unsigned n, unsigned i>
struct quadratic_recursion<n, i, 0>
{
    template<typename F>
    void operator()(F f)
    {
        quadratic_recursion<n, i-1, i-2>()(f);
    }
};
template<unsigned n>
struct quadratic_recursion<n, 2, 0>
{
    template<typename F>
    void operator()(F f)
    {
        f(Stop());
    }
};

struct PrintIndicies
{
    template<unsigned i, unsigned j, typename C>
    void operator()(C c)
    {
        using namespace std;
        cout << i << " " << j << endl;
        c(*this);
    }
    void operator()(Stop)
    {
        using namespace std;
        cout << "Stop" << endl;
    }
};

boost::array<int, 5> data = {{1, 2, 3, 4, 5}};

template<int> void ASM_MARKER(int){}

template< typename Graph = mpl::map<> >
struct Ordering
{
    template<unsigned i, unsigned j, typename C>
    void operator()(C c)
    {
        if
        (
            has_path< Graph, mpl::int_<i>, mpl::int_<j> >::type::value ||
            has_path< Graph, mpl::int_<j>, mpl::int_<i> >::type::value
        )
            c(*this);
        else if(!(data[j] < data[i]))
            c(Ordering< typename insert_directed_edge<Graph, mpl::int_<i>, mpl::int_<j> >::type>());
        else
            c(Ordering< typename insert_directed_edge<Graph, mpl::int_<j>, mpl::int_<i> >::type>());
    }
    void operator()(Stop)
    {
        using namespace std;
        const unsigned total = mpl::fold
        <
            Graph,
            mpl::int_<0>,
            mpl::plus< mpl::_1, mpl::size< mpl::second<mpl::_2> > >
        >::type::value;
        ASM_MARKER<222222>(total);
        cout << "Total: " << total << endl;
        cout << "Stop" << endl;
    }
};

int main()
{
    //quadratic_recursion<4>()(PrintIndicies());
    ASM_MARKER<11111>(1);
    quadratic_recursion<4>()(Ordering<>());
}
