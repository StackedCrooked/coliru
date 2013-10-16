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

struct printer
{
    template <typename T>
	void operator()(T) const
	{
		std::cout << typeid(T).name() << ";";
	}
};


int main()
{
	typedef fusion::result_of::as_vector<fusion::joint_view<mpl::vector<bool,std::string>,A> >::type  types1;
	typedef boost::make_variant_over<types1>::type variant1;
	
	variant1 a = 3.5f;
	variant1 b = true;
    
    std::cout << std::boolalpha;
	
	std::cout << a << " " << b << ". " << fusion::result_of::size<variant1::types>::type::value << " elements in the variant" << std::endl;
	fusion::for_each(variant1::types(),printer());
	std::cout << std::endl;
	
	typedef mpl::fold<A,mpl::set<std::string,int>,mpl::insert<mpl::_1,mpl::_2> >::type types2;
	typedef boost::make_variant_over<fusion::result_of::as_vector<types2>::type>::type variant2;

	variant2 a2 = 4;
	variant2 b2 = "bla"; 
	
	std::cout << a2 << " " << b2 << ". " << fusion::result_of::size<variant2::types>::type::value << " elements in the variant" << std::endl;
	fusion::for_each(variant2::types(),printer());
	std::cout << std::endl;
}