#include <tbb/pipeline.h>
#include <cmath>


double RootMeanSquare(double* begin, double* end)
{
    double sum = 0;
    
    auto fetch = [&](tbb::flow_control& fc) -> double*
    {
        if (begin < end)
        {
            return begin++;
        }
        fc.stop();
        return nullptr;
    };
    
    auto square = [](double* value_ptr)
    {
        auto& value = *value_ptr;
        return value * value;
    };
    
    auto store = [&](double x)
    {
        sum += x;
    };
    
    using tbb::filter;
    using tbb::make_filter;
    
    parallel_pipeline(10,
          make_filter<void   , double*>(filter::serial  , fetch )
        & make_filter<double*, double >(filter::parallel, square)
        & make_filter<double , void   >(filter::serial  , store ));

    return std::sqrt(sum);
}


#include <iostream>
#include <vector>


int main()
{
    std::vector<double> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    std::cout << RootMeanSquare(&*data.begin(), &*data.end());
}

