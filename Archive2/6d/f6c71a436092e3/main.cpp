#include <iostream>
#include <chrono>
#include <future>
#include <vector>

void spinning_threads(int thread_count, std::chrono::milliseconds t) {
    auto spin_for = [] (std::chrono::milliseconds m) {
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() < start + m)
            ;
    };
    
    std::vector<std::future<void>> futures;
    for(int i = 0; i < thread_count; ++i) {
        futures.push_back(std::async(std::launch::async, spin_for, t));
    }
}

void sleeping_threads(int thread_count, std::chrono::milliseconds t) {
    auto sleep_for = [] (std::chrono::milliseconds m) { std::this_thread::sleep_for(m); };
    
    std::vector<std::future<void>> futures;
    for(int i = 0; i < thread_count; ++i) {
        futures.push_back(std::async(std::launch::async, sleep_for, t));
    }
}

template<typename Func>
void time(Func f, int thread_count, std::chrono::milliseconds t) {
    using fsec = std::chrono::duration<double>;
    std::cout << thread_count << " threads for " << t / fsec(1) << " seconds each.\n";
    
    auto wall_start = std::chrono::steady_clock::now();
    auto cpu_start = std::clock();
    f(thread_count, t);
    auto wall_finish = std::chrono::steady_clock::now();
    auto cpu_finish = std::clock();
    
    std::cout << "Elapsed wall time: " << (wall_finish - wall_start) / fsec(1) << " seconds.\n"; 
    std::cout << "Elapsed cpu time: " << (cpu_finish - cpu_start) / double(CLOCKS_PER_SEC) << " seconds.\n"; 

}

int main() {
    int thread_count = 4;
    std::chrono::milliseconds t(100); 
    std::cout << "Sleeping ";
    time(sleeping_threads, 4, std::chrono::milliseconds(100));
    std::cout << "Spinning ";
    time(spinning_threads, 4, std::chrono::milliseconds(100));
}
