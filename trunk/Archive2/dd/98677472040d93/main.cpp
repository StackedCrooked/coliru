#include <random>
#include <iostream>
#include <functional>
#include <vector>
#include <numeric>
#include <cmath>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>

using namespace boost::accumulators;

template <typename T>
class Rand {
public:
    Rand(T lo=std::numeric_limits<T>::min(), 
         T hi=std::numeric_limits<T>::max()) : 
        r(bind(std::uniform_real_distribution<>(lo, hi),std::mt19937_64{})) {}
    T operator()() const { return r(); }
private:
    std::function<T()> r;
};

template <class T>
inline
T
sqr(T x)
{
    return x * x;
}

int main()
{
    Rand<float> f{};
    const int samples = 1000000;
    double min = std::numeric_limits<float>::max();
    double max = std::numeric_limits<float>::min();
    std::cout << "range min = " << max 
        << ", max = " << min << '\n';

    accumulator_set<double, stats<tag::min, tag::max, tag::mean, tag::variance, tag::skewness, tag::kurtosis> acc;            
    
    for (int i=0; i < samples; ++i)
        acc((double)f()); // essential to cast to double here

    min = boost::accumulators::min(acc);
    max = boost::accumulators::max(acc);
    
    std::cout << "for n = " << samples 
        << "\nsample min = " << min
        << ", max = " << max << std::endl;
    double mean = boost::accumulators::mean(acc);
    double var = boost::accumulators::variance(acc);
    double skew = boost::accumulators::skewness(acc);
    double kurtosis = boost::accumulators::kurtosis(acc);
    
    double x_mean = ((double)min + max) / 2;
    double x_var = sqr((double)max - min) / 12;
    double x_skew = 0;
    double x_kurtosis = -6./5;
    std::cout << std::scientific << '\n';
    std::cout << "            expected        actual\n";
    std::cout << "mean      " << x_mean     << "       " << mean << "\n";
    std::cout << "variance  " << x_var      << "       " << var << "\n";
    std::cout << "skew      " << x_skew     << "       " << skew << "\n";
    std::cout << "kurtosis  " << x_kurtosis << "       " << kurtosis << "\n";/**/
}