#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

template<typename F>
double timer(F function) {
   clock_t tstart, tend;

   tstart = clock();
   function();
   tend = clock();

   return ((double)tend - tstart) / CLOCKS_PER_SEC;
}

template<typename F>
std::vector<double> repeatFunction(F function) {
   std::vector<clock_t> numCalls(9);
   std::vector<double> info;

   std::generate(numCalls.begin(), numCalls.end(), [&](){ timer(function); });
   info.push_back(std::mean(numCalls));
   info.push_back(standardDeviation(numCalls));
   return info;
}

int main(void) {
   std::vector<double> x;
   x.push_back(53.0);
   x.push_back(61.0);
   x.push_back(49.0);
   x.push_back(67.0);
   x.push_back(55.0);
   x.push_back(63.0);

   std::vector<double> info = repeatFunction(std::bind(mean<double>, x));

   return 0;
}