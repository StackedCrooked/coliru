#include <boost/mpl/list.hpp>
#include <algorithm>
#include <boost/mpl/for_each.hpp>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/bind.hpp>


using namespace std;

namespace mpl = boost::mpl;


typedef mpl::range_c<char,1,5> range5;
typedef mpl::list<
mpl::int_<1>
, mpl::int_<5>
, mpl::int_<31>
, mpl::int_<14>
, mpl::int_<51>
>  out_type;


template <class T> struct id {};
struct do_this_wrapper {
    typedef void result_type;
    static char stat_c ;
    template<typename U> inline void operator()(int i, U )
    {
        if (i == U::value)
        {
            do_this_wrapper::stat_c = mpl::at_c<out_type,U::value>::type::value;
        }
    }
};


char do_this_wrapper::stat_c ;


int main()
{

    int x =1;
    boost::mpl::for_each<range5>(boost::bind(do_this_wrapper(), x, _1));

    return 0;
}