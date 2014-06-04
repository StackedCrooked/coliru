#include <iostream>
#include <deque>
#include <atomic>

int main()
{
    std::deque<std::atomic<int>> arr;
    
    arr.emplace_front(1);
}
