#include <chrono>
#include <iostream>
#include <thread>

int main() {
    auto startTime = std::chrono::steady_clock::now();
    
    using namespace std::literals;
    std::this_thread::sleep_for(3s);
    
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "Elapsed time: " << elapsedTime.count() << " milliseconds" << std::endl;
}