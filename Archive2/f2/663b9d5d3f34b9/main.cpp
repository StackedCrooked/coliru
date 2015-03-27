#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready(false);

int main()
{
    std::cout.sync_with_stdio(false);

    std::vector<std::thread> threads;
    threads.reserve(100);

    for (int i = 0; i != 25; ++i)
    {
        threads.emplace_back([](){
                while (!ready.load()) {}
                std::cerr << "This is a really very long line that doesn't quite want to end. It is really absurdly long.\n";
        });
    }

    ready.store(true);

    for (std::thread & t : threads) { t.join(); }
}
