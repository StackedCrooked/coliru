#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

template <class Type>
double round(const Type& number)
{
    return number < 0.0 ? std::ceil(number - 0.5) : std::floor(number + 0.5);
}

template <class Type>
void RandomizePiecewiseLinear(const unsigned int& iterations,
                              const std::vector<Type>& Range,
                              const std::vector<Type>& RangeValues)
{
    std::mt19937 gen(10);
    
    std::piecewise_linear_distribution<> d(Range.begin(), Range.end(),
                                           RangeValues.begin());
 
    std::map<int, unsigned int> hist;
    for(int n=0; ++n!=iterations;)
        ++hist[round(d(gen))];
    
    for(auto p : hist)
       std::cout << std::setw(2) << p.first
                 << ": "
                 << std::string(p.second/(iterations/200),'*')
                 << '\n';
}

int main()
{
    std::cout<<"PIECEWISE LINEAR DISTRIBUTION:\n";
    std::vector<double> Range;       Range       += 0, 2, 6, 14, 16, 20, 25, 30, 35, 40;
    std::vector<double> RangeValues; RangeValues += 0, 1, 3,  3,  1,  0,  1,  0,  0,  1;
    
	RandomizePiecewiseLinear(100000,
                             Range,
                             RangeValues);
    //system("pause");
}