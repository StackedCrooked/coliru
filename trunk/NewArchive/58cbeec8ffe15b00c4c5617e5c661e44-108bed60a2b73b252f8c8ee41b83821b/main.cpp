#include <iostream>
#include <chrono>

int main() {
    auto millitime = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << millitime << std::endl;
    return 0;
}