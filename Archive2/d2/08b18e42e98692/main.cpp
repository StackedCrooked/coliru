#include <iostream>
#include <string>

#include <boost/variant.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/joint_view.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/set.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/for_each.hpp>


#include <boost/mpl/fold.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/front.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

struct A
{
    int a1;
    double a2;
    float a3;
};

BOOST_FUSION_ADAPT_STRUCT(
    A,
    (int,a1)
    (double,a2)
    (float,a3)
)

struct B
{
    double b1;
    bool b2;
};

BOOST_FUSION_ADAPT_STRUCT(
    B,
    (double,b1)
    (bool,b2)
)

struct C
{
    int c1;
    std::string c2;
};

BOOST_FUSION_ADAPT_STRUCT(
    C,
    (int,c1)
    (std::string,c2)
)



struct printer
{
    template <typename T>
	void operator()(T) const
	{
		std::cout << typeid(T).name() << ";";
	}
};

template <typename Sequence>
struct build_variant_types
{
    typedef typename mpl::fold<Sequence,typename mpl::front<Sequence>::type,fusion::joint_view<mpl::_1,mpl::_2> >::type sequence_of_types;
    typedef typename fusion::result_of::as_vector<
                        typename mpl::fold<
                                    sequence_of_types,
                                    mpl::set<>,
                                    mpl::insert<mpl::_1,mpl::_2>
                        >::type
                    >::type type;
};


int main()
{
	typedef mpl::fold<fusion::joint_view<fusion::joint_view<A,B>,C>,mpl::set<>,mpl::insert<mpl::_1,mpl::_2> >::type types;
	typedef boost::make_variant_over<fusion::result_of::as_vector<types>::type>::type variant;

	variant a1 = 4;
	variant b1 = "bla"; 
	
	std::cout << a1 << " " << b1 << ". " << fusion::result_of::size<variant::types>::type::value << " elements in the variant" << std::endl;
	fusion::for_each(variant::types(),printer());
	std::cout << std::endl;
    
    typedef build_variant_types<mpl::vector<A,B,C> >::type types2;
    typedef boost::make_variant_over<types2>::type variant2;

	variant2 a2 = 4;
	variant2 b2 = "bla"; 
	
	std::cout << a2 << " " << b2 << ". " << fusion::result_of::size<variant2::types>::type::value << " elements in the variant" << std::endl;
	fusion::for_each(variant2::types(),printer());
	std::cout << std::endl;
}