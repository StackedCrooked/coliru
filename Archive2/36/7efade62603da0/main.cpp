#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include <sys/time.h>

double getRealTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (double) tv.tv_sec + 1.0e-6 * (double) tv.tv_usec;
}

int my_max_element(const std::vector<int> &vec, int size)
{
    auto it = vec.begin();
    auto res = vec.begin();
    for (; it != vec.end(); it++)
    {
        if (*it > *res)
        {
            res = it;
        }
    }
    return *res;
}

int main()
{
    const int size = 1 << 20;
    std::vector<int> vec;
    for (int i = 0; i < size; i++)
        vec.push_back(rand());

    double totalIteratorTime=0.;
    double totalArrayTime=0.;
    int maxIter, maxArray;
    for(int i=0; i<1000; ++i)
    {
        {
            double startTime = getRealTime();
            maxArray = my_max_element(vec, size);
            double stopTime = getRealTime();
            totalArrayTime += stopTime - startTime;
        }
        {
            double startTime = getRealTime();
            maxIter = *std::max_element(vec.begin(), vec.end());
            double stopTime = getRealTime();
            totalIteratorTime += stopTime - startTime;
        }
    }

    std::cout << "MaxIter = " << maxIter << std::endl;
    std::cout << "MaxArray = " << maxArray << std::endl;
    std::cout << "Total CPU time iterator = " << totalIteratorTime << std::endl;
    std::cout << "Total CPU time array = " << totalArrayTime << std::endl;
    std::cout << "iter/array ratio: = " << totalIteratorTime / totalArrayTime << std::endl;
    return 0;
}
