#include <future>
#include <thread>

int main()
{
    auto operation = []() -> int {
        while(true);
        return 42;
    };
    std::packaged_task<int()> task1(operation);
    std::packaged_task<int()> task2(operation);
    {
        std::future<int> result1 = task1.get_future();
        std::future<int> result2 = task2.get_future();
        std::thread(std::move(task1)).detach();
        std::thread(std::move(task2)).detach();
    }
}