#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

bool ready;
std::mutex mut;
std::condition_variable cv;

void callback() {
    std::cout << "Callback called\n";

    std::unique_lock<std::mutex> lock(mut);
    ready = true;
    cv.notify_all();
}

auto callAfterTime = [](auto f, auto delay) {
    std::this_thread::sleep_for(delay);
    f();
};

int main() {
    std::thread thread{[=] {callAfterTime(callback, std::chrono::seconds(2)); }};

    std::cout << "Waiting\n";
    std::unique_lock<std::mutex> lock(mut);
    cv.wait(lock, [&] {return ready; });
    std::cout << "Done\n";
    
    thread.join();
}