#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <sstream>

typedef std::unique_lock<std::mutex> lock_type;
auto t0 = std::chrono::high_resolution_clock::now();
std::mutex cout_mutex;
void log(std::string s) {
    lock_type lck(cout_mutex);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "@" << ms << " ms: " << s << std::endl;
}

auto sec = std::chrono::seconds(1);
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void task1() {
    log("Starting task 1. Waiting on cv for 2 secs.");
    lock_type lck(mtx);
    bool done = cv.wait_for(lck, 2*sec, []{return ready;});
    std::stringstream ss;
    ss << "Task 1 finished, done==" << (done?"true":"false") << ", " << (lck.owns_lock()?"lock owned":"lock not owned");
    log(ss.str());
}

void task2() {
    // Allow task1 to go first
    std::this_thread::sleep_for(1*sec);
    log("Starting task 2. Locking and sleeping 2 secs.");
    lock_type lck(mtx);
    std::this_thread::sleep_for(2*sec);
    ready = true; // This happens around 3s into the program
    log("OK, task 2 unlocking...");
    lck.unlock();
    cv.notify_one();
}

int main ()
{
    std::thread thread1(task1);
    std::thread thread2(task2);
    
    thread1.join();
    thread2.join();

    return EXIT_SUCCESS;
}