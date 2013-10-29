//             Copyright Evgeny Panasyuk 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// Reduced from larger case, some includes may not be needed

#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/value_at_key.hpp>
#include <boost/fusion/include/adapt_assoc_struct.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/algorithm.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

#include <boost/mpl/push_front.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>

using namespace boost;
using namespace std;

using fusion::at_key;
using fusion::at_c;

// ____________________________________________________________________________________ //

namespace res_of=boost::fusion::result_of;
using namespace boost::fusion;

template<typename Vector,typename First,typename Last,typename do_continue>
struct to_fusion_map_iter;

template<typename Vector,typename First,typename Last>
struct to_fusion_map_iter<Vector,First,Last,mpl::false_>
{
    typedef typename res_of::next<First>::type Next;
    typedef typename mpl::push_front
    <
        typename to_fusion_map_iter
        <
            Vector,
            Next,
            Last,
            typename res_of::equal_to<Next,Last>::type
        >::type,
        fusion::pair
        <
            typename res_of::key_of<First>::type,
            typename res_of::value_of_data<First>::type
        >
    >::type type;
};
template<typename Vector,typename First,typename Last>
struct to_fusion_map_iter<Vector,First,Last,mpl::true_>
{
    typedef Vector type;
};

template<typename FusionAssociativeSequence>
struct as_fusion_map
{
    typedef typename res_of::begin<FusionAssociativeSequence>::type First;
    typedef typename res_of::end<FusionAssociativeSequence>::type Last;
    typedef typename res_of::as_map
    <
        typename to_fusion_map_iter
        <
            mpl::vector<>,
            First,
            Last,
            typename res_of::equal_to<First,Last>::type
        >::type
    >::type type;
};

// ____________________________________________________________________________________ //

// Defenition of structure:

namespace demo
{
    struct employee
    {
        std::string name;
        int age;
    };
}

namespace keys
{
    struct name;
    struct age;
}

BOOST_FUSION_ADAPT_ASSOC_STRUCT
(
    demo::employee,
    (std::string, name, keys::name)
    (int, age, keys::age)
)

// ____________________________________________________________________________________ //
template<typename> void type_is();

int main()
{
    type_is<as_fusion_map<demo::employee>::type>();
}
