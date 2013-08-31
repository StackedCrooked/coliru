#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

template <class Type>
Type round(const Type& number)
{
    return number < 0.0 ? std::ceil(number - 0.5) : std::floor(number + 0.5);
}

template <class Type>
void RandomizePiecewiseLinear(const unsigned int& iterations,
                              const std::vector<Type>& Range,
                              const std::vector<Type>& RangeValues)
{
    std::mt19937 gen(10); // could use std:: random_device, but it is ub
    
    std::piecewise_linear_distribution<> d(Range.begin(), Range.end(),
                                           RangeValues.begin());

    std::map<int, unsigned int> hist;
    for(int n=0; ++n!=iterations;)
        ++hist[round(d(gen))]; // also notice the lack of std::round
                               // it should be in cmath, bu it is not
    
    for(auto p : hist)
       std::cout << std::setw(2) << p.first
                 << ": "
                 << std::string(p.second/(iterations/200),'*')
                 << '\n';
}

int main()
{
    std::cout<<"PIECEWISE LINEAR DISTRIBUTION:\n";
    
    double RangeTemp[]       = { 0, 2, 6, 14, 16, 20, 25, 30, 35, 40 };
    double ValueTemp[] = { 0, 1, 3,  3,  1,  0,  1,  0,  0,  1 };
    
    std::vector<double> Range(RangeTemp,
                              RangeTemp + sizeof RangeTemp / sizeof RangeTemp[0]);
    std::vector<double> Value(ValueTemp,
                              ValueTemp + sizeof ValueTemp / sizeof ValueTemp[0]);
    
    RandomizePiecewiseLinear(100000,
                             Range,
                             Value);
    //system("pause");
}