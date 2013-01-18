#include <future>
#include <thread>

int main()
{
    std::packaged_task<int()> task([]() -> int {
        while(true);
        return 42;
    });
    {
        std::future<int> result = task.get_future();
        std::thread(std::move(task)).detach();
    }
}