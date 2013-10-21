#include <iostream>
#include <thread>
#include <vector>

using namespace std;

struct Counter {
    int value;
    Counter() : value(0) {}
void increment() {
++value;
}
};

int main() {

Counter counter;
    //std::cout << counter.value << std::endl;
std::vector<std::thread> threads;

threads.push_back(std::thread([&counter]() {
for (int j = 0; j < 10; ++j) {
    int temp = counter.value;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    counter.value = temp + 1;
    std::cout << "1: " << counter.value << std::endl;
}
}));

threads.push_back(std::thread([&counter]() {
for (int j = 0; j < 10; ++j) {
int temp = counter.value;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    counter.value = temp + 1;
    std::cout << "2: " << counter.value << std::endl;
}
}));

for (auto& thread : threads) {
thread.join();
}
std::cout << counter.value << std::endl;
return 0;
}