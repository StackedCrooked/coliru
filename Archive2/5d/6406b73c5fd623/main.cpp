#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>

#include <boost/mpl/bool.hpp>

template <typename First, typename Last>
inline void
print_each_member_name(First const& first, 
    	Last const& last, 
		boost::mpl::true_) {}

template <typename First, typename Last>
inline void
print_each_member_name(First const& first, 
		Last const& last, 
		boost::mpl::false_)
{
		std::cout << boost::fusion::extension::struct_member_name<typename First::seq_type,First::index::value>::call() << '\t';
        std::cout << *first << std::endl;

		print_each_member_name(
				boost::fusion::next(first), 
				last, 
				boost::fusion::result_of::equal_to<
						typename boost::fusion::result_of::next<First>::type, Last>()
		);

}

namespace ns {
	struct point {
		int x;
		int y;
		int z;
        double allah;
	};
}

BOOST_FUSION_ADAPT_STRUCT(ns::point, (int, x) (int, y) (int, z) (double, allah))

int main(void) {
	
	ns::point mypoint = {1,2,3,3.14};

	print_each_member_name(
			boost::fusion::begin(mypoint),
			boost::fusion::end(mypoint),
			boost::mpl::false_());

}
