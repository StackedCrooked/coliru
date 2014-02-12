#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

const int TIME_BETWEEN_POLLS_MS = 50;

// Wait (sleep) between polls until a task is finished then return index.
template <typename Iterator>
Iterator finishingThread(Iterator first, Iterator last) {
    auto it = first;
    auto status = std::future_status::timeout;
    while (status != std::future_status::ready) {
        if (++it == last) {
            it = first;
        }
        status = it->wait_for(std::chrono::milliseconds(TIME_BETWEEN_POLLS_MS));
    }
    return it;
}

// Example task function that sleeps for specified time and returns thread id.
std::thread::id sleepFor(int millisec) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
    std::cout << "Terminating thread with id: " << std::this_thread::get_id() << std::endl;
    return std::this_thread::get_id();
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

    // Run tasks on separate threads.
    std::vector<std::thread> tasks;
    tasks.emplace_back(std::move(task1), 1500);
    tasks.emplace_back(std::move(task2), 500);
    tasks.emplace_back(std::move(task3), 1000);

    auto it = finishingThread(std::begin(futures), std::end(futures));

    std::cout << "We have result of the task that finished first!" << std::endl;

    // Join threads.
    for (auto& t : tasks) {
        t.join();
    }

    std::cout << "Winner result: " << it->get() << std::endl;
}