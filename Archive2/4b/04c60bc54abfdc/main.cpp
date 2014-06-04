#include <iostream>
#include <array>
#include <atomic>

int main()
{
    std::array<std::atomic<int>, 10> arr;
    
    arr[0] = 1;
    return 0;
}