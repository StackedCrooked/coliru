#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

// Function sleeps for specified time and returns thread id.
std::thread::id sleepFor(int millisec) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
    std::cout << "Thread finished: " << std::this_thread::get_id() << std::endl;
    return std::this_thread::get_id();
}

const int TIME_BETWEEN_POLLS_MS = 50;

using container_type = std::vector<std::future<std::thread::id>>;

// Wait (sleep) between polls until a thread is finished then return index.
container_type::size_type finishingThread(const container_type& futures) {
    std::future_status status = std::future_status::timeout;
    container_type::size_type i = 0;
    while (status != std::future_status::ready) {
        i = (i < futures.size() - 1) ? i + 1 : 0;
        status = futures[i].wait_for(std::chrono::milliseconds(TIME_BETWEEN_POLLS_MS));
    }
    return i;
}

int main() {
    // Create three separate tasks.
    std::packaged_task<std::thread::id(int)> task1{sleepFor},
                                             task2{sleepFor},
                                             task3{sleepFor};

    // Store futures.
    std::vector<std::future<std::thread::id>> futures;
    futures.push_back(task1.get_future());
    futures.push_back(task2.get_future());
    futures.push_back(task3.get_future());

    // Create threads.
    std::vector<std::thread> tasks;
    tasks.emplace_back(std::move(task1), 1500);
    tasks.emplace_back(std::move(task2), 500);
    tasks.emplace_back(std::move(task3), 1000);

    auto index = finishingThread(futures);

    // Join threads.
    for (auto& t : tasks) {
        t.join();
    }

    std::cout << "Thread first finnished: " << futures[index].get() << std::endl;
}