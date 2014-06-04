#include <iostream>
#include <array>
#include <deque>
#include <vector>
#include <list>
#include <atomic>

int main()
{
    {
        std::array<std::atomic<int>, 10> arr;
        arr[0] = 1;
    }
    {
        std::deque<std::atomic<int>> arr;
        arr.emplace_back(1);
    }
    {
        std::list<std::atomic<int>> arr;
        arr.emplace_back(1);
    }
    {
        std::vector<std::atomic<int>> arr;
        arr.emplace_back(1);
    }
}
