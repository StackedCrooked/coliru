#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <boost/exception/detail/type_info.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/timer/timer.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>

#if defined(__GNUC__)
    #define NOINLINE __attribute__ ((noinline))
#elif defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#else
    #define NOINLINE
#endif

template<int> NOINLINE void ASM_MARKER() { volatile int x = 0; (void)x; }

/******************************************************************************/
using namespace std;

template<typename Range>
void test(Range &r)
{
    cout << boost::type_name<Range>() << ": ";

    boost::timer::auto_cpu_timer t;

    ASM_MARKER<111>();
    volatile int result = boost::accumulate(r, 0);
    ASM_MARKER<222>();

    (void)result;
}

int main() try
{
    vector<int> v(8000000);
    boost::iota(v, 0);
    boost::random_shuffle(v);

    list<int> l(begin(v), end(v));

    l.sort();
    boost::sort(v);

    test(v);
    test(l);
    test(v);
    test(l);
}
catch(const exception &e)
{
    cout << e.what() << endl;
}