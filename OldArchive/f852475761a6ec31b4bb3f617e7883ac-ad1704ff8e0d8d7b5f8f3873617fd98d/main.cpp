#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <type_traits>

using namespace boost;
using namespace boost::mpl;

template <typename VECTOR>
struct first_element : mpl::at_c<VECTOR, 0> {};

int main()
{
    typedef vector<
        vector<int, int>,
        vector<int, int>,
        vector<int, int>> lotso;

    typedef mpl::transform<lotso,
        first_element<_1>>::type inst1;

    typedef first_element<
        at_c<lotso,0>::type >::type inst2;

    static_assert(std::is_same<first_element<inst1>::type, inst2>::value, "bingo");

    return 0;
}