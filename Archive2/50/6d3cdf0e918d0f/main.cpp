#include <array>
#include <chrono>
#include <future>
#include <thread>

int main()
{
    std::array<std::future<void>, 1000> futures;

    for (auto& f : futures)
    {
        f = std::async(std::launch::async, []{
            std::async(std::launch::async, []{
              std::this_thread::sleep_for(std::chrono::milliseconds{50});
            });
        });
    }
}
