#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <sys/time.h>

double getRealTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (double) tv.tv_sec + 1.0e-6 * (double) tv.tv_usec;
}

inline int my_max_element(const std::vector<int> &vec, int size)
{
    auto it = vec.begin();
    int max = *it++;
    for (; it != vec.end(); it++)
    {
        if (*it > max)
        {
            max = *it;
        }
    }
    return max;
}

int main()
{
    const int size = 1 << 20;
    std::vector<int> vec;
    for (int i = 0; i < size; i++)
    {
        if (i == 59)
        {
            vec.push_back(1000000012);
        }
        else
        {
            vec.push_back(i);
        }
    }

    double startTime = getRealTime();
    int maxIter = *std::max_element(vec.begin(), vec.end());
    double stopTime = getRealTime();
    double totalIteratorTime = stopTime - startTime;

    startTime = getRealTime();
    int maxArray = my_max_element(vec, size);
    stopTime = getRealTime();
    double totalArrayTime = stopTime - startTime;

    std::cout << "MaxIter = " << maxIter << std::endl;
    std::cout << "MaxArray = " << maxArray << std::endl;
    std::cout << "Total CPU time iterator = " << totalIteratorTime << std::endl;
    std::cout << "Total CPU time array = " << totalArrayTime << std::endl;
    std::cout << "iter/array ratio: = " << totalIteratorTime / totalArrayTime << std::endl;
    return 0;
}