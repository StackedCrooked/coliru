urn std::accumulate(beg, end, 0);
 
    RAIter mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                              parallel_sum<RAIter>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 
template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
    auto len = std::distance(beg, end);
    if(len < 1000)
        ret
 
int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}