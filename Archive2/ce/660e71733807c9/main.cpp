#include <iostream>
#include <list>
#include <atomic>

int main()
{
    std::list<std::atomic<int>> arr(10);
    
    arr.front() = 1;
    return 0;
}
