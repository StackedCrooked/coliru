#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 
template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
    auto len = std::distance(beg, end);
    if(len < 1000)
        return std::accumulate(beg, end, 0);
 
    RAIter mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                              parallel_sum<RAIter>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

class Listener
{
public:
    void print(int i)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "the sum = " << i << std:: endl;
    }
private:
    std::mutex m_mutex;
 };


int main()
{
    // std::vector<int> v(10000, 1);
    // std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
    int i = 0;
    int j = 1;
    auto listener = std::make_shared<Listener>();
    auto handle = std::async(std::launch::async, 
        [i](int &&j, std::shared_ptr<Listener> listener){
            int sum = i+j;
            listener->print(sum);
        }, std::move(j), listener);
        
    // std::cout << "after swap(j), j = " << j << std::endl;
    handle.wait();
}