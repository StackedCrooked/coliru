#include <random>
#include <iostream>
#include <array>

int main() {
    using RandomGenType = std::mt19937_64;
    RandomGenType gen(1230123);
    
    std::array<double,5> intervals {0.59e-3, 0.7e-3, 0.85e-3, 1e-3, 1.18e-3};
    std::array<double,4> weights {2*1.36815, 2*1.99139, 2*0.29116, 2*0.039562};
    std::piecewise_constant_distribution<double>
    distribution (intervals.begin(),intervals.end(),weights.begin());
    
    const unsigned int n = 1000000;
    std::array<unsigned long long, 6> counts = {{}};
    
    for(unsigned i=0;i<n;i++){
        auto d = distribution(gen);
        if (d<intervals[0])
            ++counts[0];
        else if (d<intervals[1])
            ++counts[1];
        else if (d<intervals[2])
            ++counts[2];
        else if (d<intervals[3])
            ++counts[3];
        else if (d<intervals[4])
            ++counts[4];
        else
            ++counts[5];
    }
    
    double totalweight = std::accumulate(weights.begin(), weights.end(),0.0);
    for(int i=0; i<6; ++i) {
        double proportion = counts[i]*1.0/n;
        double wantproportion = (i>0 && i<5) ? weights[i-1]/totalweight : 0.0;
        double ratio = wantproportion ? proportion/wantproportion : 0.0;
        std::cout << proportion << '\t' << wantproportion << '\t' << ratio << '\n';
    }
}