#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <omp.h>

using namespace std;

template<typename I, typename O, typename F>
// requires( RandomAccessIterator(I) && RandomAccessIterator(O) &&
//           UnaryFunction(F) && ValueType(I) == Domain(F) && ValueType(O) == Codomain(F) )
void parallel_for_each(I first, I last, O out, F f)
{
    typedef typename std::iterator_traits<I>::difference_type iter_diff;

    iter_diff size = distance(first, last);
    #pragma omp parallel for
    for(iter_diff i = 0; i < size; ++i)
        try
        {
            out[i] = f( first[i] );
        }
        catch(...){}
}


int main()
{
    vector<double> v(1u << 24);
    parallel_for_each( begin(v), end(v), begin(v), [](double) { return 1.0 + double(rand() % 10); } );
    parallel_for_each( begin(v), end(v), begin(v), [](double x) { return x*2.0 + 11.0; } );
}
