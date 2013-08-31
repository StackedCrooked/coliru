#include <algorithm>
#include <thread>
#include <future>
#include <iostream>
#include <iterator>
#include <vector>

const std::size_t not_found = -1;

template <typename Iterator, typename T>
std::size_t find_index(Iterator begin, Iterator end, 
                       const T& value, std::size_t start)
{
    std::size_t s = start;
    Iterator it = begin;
    
    while(it != end) {
        if(*it == value) {
            return s;
        }
        ++s;
        ++it;
    }
    
    return not_found;
}

int main()
{
    std::vector<int> v { 4, 5, 1, 3, 9, 8, 7, 6, 11, 42, 13 };
    typedef typename std::vector<int>::iterator iter_t;
    
    std::vector<std::future<std::size_t>> futures;
    futures.emplace_back(
        std::async(std::launch::async, find_index<iter_t, int>, 
                   v.begin(), v.begin() + 6, 8, 0));
    futures.emplace_back(
        std::async(std::launch::async, find_index<iter_t, int>, 
                   v.begin() + 6, v.end(), 8, 6));
    
    std::vector<std::size_t> results;
    for(auto& future : futures) {
        results.emplace_back(future.get());
    }
    
    std::for_each(results.begin(), results.end(),
                  [](std::size_t index)
                  { if(index != not_found) std::cout << index << "\n"; });
}
