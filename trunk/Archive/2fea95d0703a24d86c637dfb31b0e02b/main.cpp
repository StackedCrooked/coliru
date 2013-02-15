#include <future>
#include <thread>

int main()
{
    std::future<int> result = std::async(std::launch::async, []() -> int {
        while(true);
        return 42;
    });
}