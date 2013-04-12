#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <random>

#include <boost/assign/std/vector.hpp>
using namespace boost::assign;
 
double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

template <typename distribution>
void randomize(int iterations, int A, int B)
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    distribution d(A,B);
 
    std::map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[round(d(gen))];
    }
    for(auto p : hist)
    {
        //std::cout << std::setw(2) << p.first << ": " << p.second << '\n';
       std::cout << std::setw(2) << p.first << ": "
                                  << std::string(p.second/(iterations/200),'*')
                                  <<'\n';//*/
    }
}

template <typename Type>
void RandomizePiecewiseLinear(const std::vector<Type>& Range, const std::vector<Type>& RangeValues)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::piecewise_linear_distribution<> d(Range.begin(), Range.end(), RangeValues.begin());


    std::map<int, int> hist;
    for(int n=0; n<10000; ++n)
    	++hist[round(d(gen))];
    /*
	std::vector<int> Ans(Range.size()-1,0);
	int itV = 0;
	for(auto itH = hist.begin(), itHE=hist.end(); itH!=itHE; ++itH)
	{
		if ((*itH).first);
	}*/

    for(auto p : hist) {
        std::cout << std::setw(2) << p.first << ": " << std::string(p.second/100, '*') << '\n';
    }
}

int main()
{
	/*
	std::cout<<"UNIFORM:\n";
	randomize<std::uniform_int_distribution<>>(10000,-10,10);
	std::cout<<"NORMAL:\n";
	randomize<std::normal_distribution<>>(10000,0,3);//*/
	std::cout<<"PIECEWISE LINEAR DISTRIBUTION:\n";
	std::vector<double> i; i+= 0, 2, 6, 14, 16, 20, 25, 30, 35, 40;
    std::vector<double> w; w+= 0, 1, 3,  3,  1,  0,  1,  0,  0,  1;
	RandomizePiecewiseLinear(i,w);

	//system("pause");
}