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

template<typename _ForwardIterator, typename _Compare>
_ForwardIterator
my_max_element(_ForwardIterator __first, _ForwardIterator __last,
_Compare __comp)
{
     if (__first == __last) return __first;
     _ForwardIterator __result = __first;
     ++__first;
     for(; __first != __last; ++__first)
          if (__comp(__result, __first))
               __result = __first;
     return __result;
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
    int maxArray = *std::max_element(vec.begin(), vec.end());
    stopTime = getRealTime();
    double totalArrayTime = stopTime - startTime;

    std::cout << "MaxIter = " << maxIter << std::endl;
    std::cout << "MaxArray = " << maxArray << std::endl;
    std::cout << "Total CPU time iterator = " << totalIteratorTime << std::endl;
    std::cout << "Total CPU time array = " << totalArrayTime << std::endl;
    std::cout << "iter/array ratio: = " << totalIteratorTime / totalArrayTime << std::endl;
    return 0;
}