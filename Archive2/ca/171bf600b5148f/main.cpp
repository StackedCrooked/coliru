#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <iomanip>      // std::setprecision
#include <fstream>
#include <cmath>
#include <array>
#include <random>

int main()
{
   using PREC = double;
    std::array<PREC,5> intervals {0.5, 0.7, 0.8, 1, 1.2};
    std::array<PREC,4> weights   {1.5, 3, 0.5, 0.1};
    
    // Make the distribution and check densities
    std::piecewise_constant_distribution<PREC>
    distribution (intervals.begin(),intervals.end(),weights.begin());

    std::cout << "Densities std::piecewise_constant_distribution: ";
    auto d = distribution.densities();
    std::copy(d.begin(), d.end(), std::ostream_iterator<PREC>(std::cout, " "));
    std::cout << std::endl;
    
    // Get the densities manually
    // integral over the pdf to normalize:
    PREC normalization =0;
    for(unsigned int i=0;i<4;i++){
        normalization += weights[i]*(intervals[i+1]-intervals[i]);
    }
    std::cout << std::setprecision(30) << "Normalization: " << normalization << std::endl;
    
    std::cout << "Densities what they should be: " << std::endl;
    // accroding to http://www.cplusplus.com/reference/random/piecewise_constant_distribution/
    for(auto & w : weights){
        // normalize all weights (such that the integral gives 1)!
        w /= normalization;
        std::cout << "Probability : " << w <<std::endl;
    }
}
