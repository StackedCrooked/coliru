#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 
template <typename T>
int parallel_sum(T beg, T end)
{
    auto len = std::distance(beg, end);
    if(len < 1000)
        return std::accumulate(beg, end, 0);
 
    T mid = beg + len/2;
    auto handle = std::async(std::launch::async, parallel_sum<T>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}