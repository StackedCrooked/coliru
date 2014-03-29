#include <iostream>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/int.hpp>

namespace mpl = boost::mpl;

template<class N> struct __Fibonacci : 
    mpl::eval_if<
		mpl::less_equal<N,mpl::int_<1> >,
		N,
		mpl::plus<
			__Fibonacci<
				typename mpl::minus<
					N,mpl::int_<1>
				>::type
			>,
			__Fibonacci<
				typename mpl::minus<
					N,mpl::int_<2>
				>::type
			>
		>
	>::type{
};

template<int N> struct Fibonacci :
	__Fibonacci<mpl::int_<N> >::type{
};

int main(){
	std::cout << Fibonacci<20>::value << std::endl;
	return 0;
}
