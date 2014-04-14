#include <iostream>
#include <boost/preprocessor.hpp>

#define EMPTY(a) BOOST_PP_CAT(EMPTY_, BOOST_PP_BOOL(a))
#define EMPTY_BOOST_PP_BOOL_ 1
#define EMPTY_0 0
#define EMPTY_1 0

#define EMPTY_OR(x, y) BOOST_PP_IF(EMPTY(x), (y), (x))

using namespace std;

int main()
{
    int four = EMPTY_OR(4, );
    int eight = EMPTY_OR(4, 8);
    cout << "four: " << four << endl;
    cout << "eight: " << eight << endl;
    return 0;
}