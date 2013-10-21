#include <iostream>
#include <thread>
#include <vector>
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
counter.increment();
std::cout << "1: " << counter.value << std::endl;
}
}));

threads.push_back(std::thread([&counter]() {
for (int j = 0; j < 10; ++j) {
counter.increment();
std::cout << "2: " << counter.value << std::endl;
}
}));

for (auto& thread : threads) {
thread.join();
}
std::cout << counter.value << std::endl;
return 0;
}