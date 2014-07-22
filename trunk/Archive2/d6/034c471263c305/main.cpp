#include <boost/mpl/vector.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/at.hpp>

template<class, class> class A{};
template<class A, template<class, class> class C>
class B{
    C<A, B*> _c;
};
using T = boost::mpl::vector < int, boost::mpl::quote2<A> > ;
using T1 = boost::mpl::at<T, boost::mpl::int_<0>>::type;
using T2 = boost::mpl::at<T, boost::mpl::int_<1>>::type;

template<typename X1, typename X2>
using TT2 = typename boost::mpl::apply<T2, X1, X2>::type;

int main()
{
    B<T1, TT2> b;
}
