#include <boost/progress.hpp>
#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

using namespace boost;
using namespace std;

inline double calc(double x)
{
    return ( tanh( 3*(5-x)  ) *0.5 + 0.5);
}

template<typename F>
void test(F &&f)
{
   progress_timer t;
   volatile double res;
   for(unsigned i=0;i!=1<<26;++i)
      res = f(i);
   (void)res;
}

int main()
{
   const unsigned size = (1 << 26) + 1;
   vector<double> table(size);
   cout << "table size is " << 1.0*sizeof(double)*size/(1 << 20) << "MiB" << endl;
   cout << "calc ";
   test(calc);
   cout << "dummy lookup ";
   test([&](unsigned i){return table[(i << 12)%size];}); // dummy lookup, not real values
}
