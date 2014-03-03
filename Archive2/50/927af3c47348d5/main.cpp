#include <iostream>
#include <stdlib.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>

using namespace boost::accumulators;

// set up the various accumulators
typedef accumulator_set<int, stats<tag::variance> > Var;
typedef accumulator_set<int, stats<tag::variance, tag::kurtosis> > VarKurt;
typedef accumulator_set<int, stats<tag::variance, tag::mean> > VarMean;
typedef accumulator_set<int, stats<tag::variance, tag::mean, tag::kurtosis> > VarMeanKurt;

Var accumulate_Var(int *v, int n) {
    Var acc;
  for(unsigned int i=0; i<n; i++) {
   acc(v[i]);
  }
  return acc;
}

VarKurt accumulate_VarKurt(int *v, int n) {
  VarKurt acc;
  for(unsigned int i=0; i<n; i++) {
       acc(v[i]);
  }
  return acc;
}

VarMean accumulate_VarMean(int *v, int n) {
  VarMean acc;
  for(unsigned int i=0; i<n; i++) {
       acc(v[i]);
  }
  return acc;
}

VarMeanKurt accumulate_VarMeanKurt(int *v, int n) {
  VarMeanKurt acc;
  for(unsigned int i=0; i<n; i++) {
      acc(v[i]);
  }
  return acc;
}

int main(int argc, char *argv[]) {
   int n=argc-1;
   int x[n];
   for (int i=1; i<=n; i++) {
     x[i-1] = atoi(argv[i]);
   }
   
   std::cout << "boost version " << BOOST_VERSION << std::endl;

   std::cout << std::endl << " Variances: " << std::endl;
   std::cout << "        Var: " << variance(accumulate_Var(x, n)) << std::endl;
   std::cout << "    VarKurt: " << variance(accumulate_VarKurt(x, n)) << std::endl;
   std::cout << "    VarMean: " << variance(accumulate_VarMean(x, n)) << std::endl;
   std::cout << "VarMeanKurt: " << variance(accumulate_VarMeanKurt(x, n)) << std::endl;

   return 0;
}