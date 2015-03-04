#include <iostream>
#include <string>
#include <vector>


#include <cmath>
#include <array>
#include <random>

void calculateExpectedMass(){

    using RandomGenType = std::mt19937_64;
    RandomGenType gen(51651651651);

    std::array<double,5> intervals {0.59, 0.7, 0.85, 1, 1.18};
    std::array<double,4> weights {2*1.36815, 2*1.99139, 2*0.29116, 2*0.039562};
    std::piecewise_constant_distribution<double>
    distribution (intervals.begin(),intervals.end(),weights.begin());
    
    // add this to make PDF integrate to almost 1 --> does not change anything
    /*for(auto & i : intervals){
        i+= 3.18644e-6;
    }*/

    unsigned int n = 1000000;
    double density = 2400;
    double mass = 0;

    for(unsigned int i=0;i<n;i++){
        auto d = 2* distribution(gen)*1e-3;
        mass += d*d*d/3.0*M_PI_2*density;
    }

    std::cout << "Mass for n: "<< n << " spheres  with density: " << density << " = " << mass << " kg"<< std::endl;
}


int main()
{
    calculateExpectedMass();
    calculateExpectedMass();
    calculateExpectedMass();
    calculateExpectedMass();
    calculateExpectedMass();
}
