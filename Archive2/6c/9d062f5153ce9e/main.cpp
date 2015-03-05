#include <iostream>
#include <string>
#include <vector>
#include <iomanip>      // std::setprecision

#include <cmath>
#include <array>
#include <random>

int main()
{
    using RandomGenType = std::mt19937_64;
    RandomGenType gen(51651651651);
    using PREC = long double;
    std::array<PREC,5> intervals {0.59, 0.7, 0.85, 1, 1.18};
    std::array<PREC,4> weights {1.36814, 1.99139, 0.29116, 0.039562};


     // integral over the pdf to normalize:
    PREC integral =0;
    for(unsigned int i=0;i<4;i++){
        integral += weights[i]*(intervals[i+1]-intervals[i]);
    }
    std::cout << std::setprecision(30) << "Normalization: " << integral << std::endl;
    // normalize all weights (such that the integral gives 1)!
    for(auto & w : weights){
        w /= integral;
    }


    std::piecewise_constant_distribution<PREC>
    distribution (intervals.begin(),intervals.end(),weights.begin());

    unsigned int n = 1000000;
    PREC density = 2400;
    PREC mass = 0;


    std::vector<PREC> masses(n);

    for(unsigned int i=0;i<n;i++){
        auto d = 2* distribution(gen)*1e-3;
        masses[i] = d*d*d/3.0*M_PI_2*density;
        mass += masses[i];
    }


    // Do reduction (to sum up more accurately)
    unsigned int stride = 1;
    while(stride < n){
           for(unsigned int i = 0; i<n ; i+=2*stride){
                if(i+stride < n){
                    masses[i] += masses[i+stride];
                }
           }
           stride*=2;
    }
    // result is in masses[0];


    std::cout <<std::setprecision(30) << "Mass for n: "<< n << " spheres  with density: " << density << " = \t" << mass << " kg"<< std::endl;
    std::cout                         << "Mass computed by reduction: \t\t\t\t" << masses[0] << std::endl;
}
