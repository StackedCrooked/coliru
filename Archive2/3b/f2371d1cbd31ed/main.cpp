//             Copyright Evgeny Panasyuk 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Sorting via ordering memoization in compile-time graph for C++98

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/sort.hpp>
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

#include <boost/exception/detail/type_info.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config/suffix.hpp>
#include <boost/progress.hpp>

#include <boost/range/algorithm_ext.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <vector>

using namespace boost;


#ifdef _MSC_VER
    #define TEMPLATE_MEMBER
#else
    #define TEMPLATE_MEMBER template
#endif

#if defined(__GNUC__)
    #define NOINLINE __attribute__ ((noinline))
#elif defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#else
    #define NOINLINE
#endif

template<int> void ASM_MARKER(int);

/*****************************************************************************/
// Compile-time graph (adjacency list) with two main operations:
// insert_directed_edge(graph, from, to)
// has_path(graph, from, to)

typedef mpl::map<> empty_graph;

template
<
    typename AdjacencyList,
    typename Vertex,
    typename Default = mpl::set<>
>
struct adjacent_vertices
{
    typedef typename mpl::eval_if
    <
        mpl::has_key<AdjacencyList, Vertex>,
        mpl::at<AdjacencyList, Vertex>,
        mpl::identity<Default>
    >::type type;
};

template
<
    typename AdjacencyList,
    //typename From,
    typename To,
    typename Queue, // = mpl::deque< From >,
    typename Visited = mpl::set<>
>
struct has_path_aux
{
    typedef typename mpl::front<Queue>::type head;
    typedef typename adjacent_vertices<AdjacencyList, head>::type adjacent;

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
            has_path_aux<AdjacencyList, To, new_queue, new_visited>
        >::type
    >::type type;
};

template
<
    typename AdjacencyList,
    typename From, typename To
>
struct has_path // breadth-first search
{
    typedef typename has_path_aux< AdjacencyList, To, mpl::deque< From > >::type type;
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
                typename adjacent_vertices<AdjacencyList, From>::type,
                To
            >::type
        >
    >::type type;
};

/*****************************************************************************/
// Driver which calls given function object with
// 2-combinations from set [0, n) via continuation-passing style
// (i.e. next iteration is passed as argument to given function object).
// 2-combinations are generated in ascending lexicographical order
// i.e.: (0,1), (0,2), (0,3), ..., (0,n-1), (1,2), (1,3), ..., (n-2,n-1)

template<unsigned N> struct combination_stop {};

template<unsigned N, unsigned I=N, unsigned J=I-1>
struct combinations_of_two
{
    enum{ inner = N-J, outter = N-I };
    
    template<typename F> BOOST_FORCEINLINE
    void operator()(F f)
    {
        f.TEMPLATE_MEMBER operator()<outter, inner>
        (
            combinations_of_two<N, I, J-1>()
        );
    }
};

template<unsigned N, unsigned I>
struct combinations_of_two<N, I, 0>
{
    template<typename F> BOOST_FORCEINLINE
    void operator()(F f)
    {
        combinations_of_two<N, I-1, I-2>()(f);
    }
};

template<unsigned N>
struct combinations_of_two<N, 2, 0>
{
    template<typename F> BOOST_FORCEINLINE
    void operator()(F f)
    {
        f(combination_stop<N>());
    }
};

/*****************************************************************************/
// Auxiliary stuff for unrolled copy

template<typename RndItIn, typename RndItOut>
struct copier
{
    RndItIn first;
    RndItOut out;
    copier(RndItIn first, RndItOut out) : first(first), out(out) {}

    template<typename Pair>
    void operator()(Pair)
    {
        out[mpl::at_c<Pair, 0>::type::value] = first[mpl::at_c<Pair, 1>::type::value];
    }
};

/*****************************************************************************/
// Function object of following type performs comparsion of
// given pair of elements, and stores result in compile-time graph.
// If result of comparison can be deduced from current graph, then 
// comparison is not performed.
// At the last step, it passes gathered graph into given function object.

template< typename RndItIn, typename F, typename Graph = empty_graph >
struct ordering
{
    RndItIn first;
    F f;
    ordering(RndItIn first, F f) : first(first), f(f) {}

    template<unsigned from, unsigned to>
    struct local_insert_directed_edge // Helper with current type context
    {
        typedef mpl::integral_c<unsigned, from> From;
        typedef mpl::integral_c<unsigned, to> To;

        typedef ordering
        <
            RndItIn, F,
            typename insert_directed_edge<Graph, From, To>::type
        > type;
    };

    template<unsigned from, unsigned to>
    struct less_deducable
    {
        typedef mpl::integral_c<unsigned, from> From;
        typedef mpl::integral_c<unsigned, to> To;

        enum
        {
            value = has_path
            <
                Graph,
                From, To
            >::type::value
        };
    };

    template<unsigned i, unsigned j, typename C> BOOST_FORCEINLINE
    typename boost::enable_if_c
    <
        less_deducable<i, j>::value || less_deducable<j, i>::value
    >::type operator()(C continuation)
    {
        // Do not compare, because relationship can be deduced from graph,
        // just pass.
        continuation(*this);
    }

    template<unsigned i, unsigned j, typename C> BOOST_FORCEINLINE
    typename boost::disable_if_c
    <
        less_deducable<i, j>::value || less_deducable<j, i>::value
    >::type operator()(C continuation)
    {
        // Relationship cannot be deduced from graph,
        // perform comparison and store result in compile-time graph.
        if(!(first[j] < first[i]))
            continuation(typename local_insert_directed_edge<i, j>::type(first, f));
        else
            continuation(typename local_insert_directed_edge<j, i>::type(first, f));
    }

    template<unsigned N> BOOST_FORCEINLINE
    void operator()(combination_stop<N>)
    {
        // Last iteration, pass Graph into given function object
        f.TEMPLATE_MEMBER operator()<Graph, N>(first);
    }
};

/*****************************************************************************/
// Sorts counted range [first, N) into given RandomAccessRange,
// via given Graph ordering.

template<typename RndItOut>
struct sort_by_graph_ordering
{
    RndItOut out;
    sort_by_graph_ordering(RndItOut out) : out(out) {}

    template<typename Graph, unsigned N, typename RndItIn>
    void operator()(RndItIn first)
    {
        /*using namespace std;
        const unsigned total = mpl::fold
        <
            Graph,
            mpl::int_<0>,
            mpl::plus< mpl::_1, mpl::size< mpl::second<mpl::_2> > >
        >::type::value;
        cout << "Total edges count in ordering graph: " << total << endl;*/

        typedef mpl::range_c<unsigned, 0, N> identity_permutation;

        typedef typename mpl::sort
        <
            identity_permutation,
            has_path<Graph, mpl::_1, mpl::_2>, // use Graph as Ordering predicate
            mpl::back_inserter< mpl::vector<> >
        >::type sorting_permutation;

        mpl::for_each
        <
            mpl::zip_view< mpl::vector<identity_permutation, sorting_permutation> >
        >(copier<RndItIn, RndItOut>(first, out));
    }
};

/*****************************************************************************/
// Putting it all together:

template<unsigned N, typename RndItIn, typename RndItOut>
BOOST_FORCEINLINE
//NOINLINE
void ctom_sort_copy(RndItIn first, RndItOut out)
{
    //ASM_MARKER<11111>(1);
    // As optimization, it is possible to do additional preliminary traversal of
    // pairs in order which is more likely to be sorted, i.e. something like (i, i+1)
    typedef sort_by_graph_ordering<RndItOut> S;
    combinations_of_two<N>()(ordering<RndItIn, S>(first, S(out)));
    //ASM_MARKER<22222>(2);
}

template<unsigned N, typename RndItIn>
BOOST_FORCEINLINE
//NOINLINE
void ctom_sort(RndItIn first)
{
    //ASM_MARKER<33333>(1);
    typedef typename std::iterator_traits<RndItIn>::value_type T;
    T buffer[N];
    ctom_sort_copy<N>(first, boost::begin(buffer));

    typedef mpl::range_c<unsigned, 0, N> seq;
    mpl::for_each
    <
        mpl::zip_view< mpl::vector<seq, seq> >
    >( copier<T*, RndItIn>(boost::begin(buffer), first) );
    //std::copy_n(boost::begin(buffer), N, first);
    //ASM_MARKER<44444>(2);
}

/*****************************************************************************/
// Wrappers around sortings:

struct Introsort
{
    template<unsigned N, typename I>
    static void call(I i)
    {
        std::sort(i, i+N);
    }
};

struct Heapsort
{
    template<unsigned N, typename I>
    static void call(I i)
    {
        std::partial_sort(i, i+N, i+N);
    }
};

struct Mergesort
{
    template<unsigned N, typename I>
    static void call(I i)
    {
        std::stable_sort(i, i+N);
    }
};


struct CompileTimeOrderMemoizationSort
{
    template<unsigned N, typename I>
    static void call(I i)
    {
        ctom_sort<N>(i);
    }
};

/*****************************************************************************/
// Testing stuff:

template<typename Range>
void print(const Range &x)
{
    using namespace std;

    typedef typename boost::range_value<Range>::type T;
    boost::copy(x, ostream_iterator<T>(cout, " "));
    cout << endl;
}

struct anti_opti
{
    template<typename T>
    void operator()(T x)
    {
        volatile T y = x;
        (void)y;
    }
};

template<typename Sort, unsigned N, typename Data>
void test(const Data &data)
{
    using namespace std;
    cout << boost::type_name<Sort>() << ": ";
    typedef typename boost::range_iterator<Data>::type I;
    Data x = data;
    {
        boost::progress_timer t;
        for(unsigned j=0; j!=1u << 10; ++j)
        {
            for(I i = boost::begin(x); i!= boost::end(x); i+=N)
            {
                Sort::template call<N>(i);
                //assert(boost::is_sorted(boost::make_iterator_range(i, i+N)));
            }

            boost::for_each(x, anti_opti());
            x = data;
        }
    }
}

template<unsigned N>
class Tester
{
    
    std::vector<double> x;
public:
    Tester()
        : x(N * (1u << 13))
    {
        boost::iota(x, 1.0);
        boost::random_shuffle(x);
    }

    template<typename Sort>
    void operator()(Sort)
    {
        test<Sort, N>(x);
    }
};

/*****************************************************************************/

int main()
{
    enum{ N = 4 };
    {
        double data[] = {3., 4., 2., 5., 0., 1.};
        print(data);
        ctom_sort<N>(boost::begin(data));
        print(data);
    }

    typedef mpl::vector
    <
        Introsort, Heapsort, Mergesort, CompileTimeOrderMemoizationSort
    > sortings;

    for(int i=0; i!=2; ++i)
        mpl::for_each<sortings>( Tester<N>() );
}

