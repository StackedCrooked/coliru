#include <iostream>
#include <thread>

static const int kLoopCount = 1000000;

int kCount = 0;

void TaskTwo(void) {
    for (auto i = 0; i < kLoopCount; ++i) {
        kCount = kCount + 1;
    }
}

void TaskOne() {
    for (auto i = 0 ; i< kLoopCount; ++i) {
        kCount = kCount + 1;
    }
}
int main() {
    std::thread one(TaskOne);
    std::thread two(TaskTwo);
    
    one.join();
    two.join();
    
    std::cout << kCount << std::endl;
    return 0;
}
