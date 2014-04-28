#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <algorithm>
//#include "median.h"

// mutex to protect bgrPixel (possibly not needed)
std::mutex mtx;

void thread_function(std::vector<int>& bgrPixel, const std::vector<std::vector<int> >&                 input1, int channel)
{
    std::vector<int> input = input1[channel];  // copy the colour channel
    std::sort(input.begin(), input.end());
    int size = input.size();
    if (size %2 == 0)   // get the median
    {
        mtx.lock();
        bgrPixel[channel] = (input[size/2] + input[size/2 + 1])/2;
        mtx.unlock();
    } else
    {
        mtx.lock();
        bgrPixel[channel] = input[(size-1)/2];
        mtx.unlock();
    }
}

std::vector<int> median(const std::vector<std::vector<int> >& input)
{
    std::vector<int> bgrPixel(input.size());
    std::thread first(thread_function, std::ref(bgrPixel), std::ref(input), 0); // thread for each colour channel
    std::thread second(thread_function, std::ref(bgrPixel), std::ref(input), 1);
    std::thread third(thread_function, std::ref(bgrPixel), std::ref(input), 2);
    first.join();
    second.join();
    third.join();
    return bgrPixel;
}


int main()
{
    for (auto e : median({{3,2,1}, {1,2,3}, {2,2,2}})) {
        std::cout << e << std::endl;
    }
    return 0;
}
