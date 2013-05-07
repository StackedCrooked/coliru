#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx; 

void print(const std::string& msg)
{
    std::lock_guard<std::mutex> lock(mtx); // scoped lock
    std::cout << msg << std::flush;
}

int main()
{
    // Create 10 threads that each call print function repeatedly.
    std::vector<std::thread> threads;
    for (int i = 0; i != 10; ++i) {
        threads.emplace_back([i]{
            for (int j = 0; j != 100; ++j) {
                print(std::to_string(i) + '.' + std::to_string(j) + '\n');
            }
        });
    }
    
    // wait for each thread to complete
    for (auto& t : threads) {
        t.join();
    }
}