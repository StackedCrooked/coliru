#include <iostream>
#include <string>
#include <vector>


#include <cmath>
#include <array>
#include <random>

void calculateExpectedMass(){

    int seed = 5;
    using RandomGenType = std::mt19937_64;
    //using RandomGenType = std::random_device;
    RandomGenType gen(seed);

    std::array<double,5> intervals {0.59e-3, 0.7e-3, 0.85e-3, 1e-3, 1.18e-3};
    std::array<double,4> weights {1.36815, 1.99139, 0.29116, 0.039562};
    std::piecewise_constant_distribution<double>
    distribution (intervals.begin(),intervals.end(),weights.begin());

    unsigned int n = 1000000;
    double density = 2400;
    double mass = 0;
    for(unsigned int i=0;i<n;i++){
        auto d = 2* distribution(gen);
        double m = d*d*d/3.0*M_PI_2*density;
        mass +=m;
 
    }
    std::cout << "Mass for n: "<< n << " spheres  with density: " << density << " = " << mass << " kg"<< std::endl;
}


int main()
{
    calculateExpectedMass();
}
