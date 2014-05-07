#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>
 
std::mutex m;
std::condition_variable cv;
std::atomic_bool is_cancelled(false);
typedef std::pair<std::chrono::system_clock::time_point, int> Key;
std::priority_queue<Key, std::vector<Key>, std::greater<Key>> keys;

void callback(int key) {
    long current_time_in_seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<key<<' '<<current_time_in_seconds<<std::endl;
}

void call_later(std::chrono::milliseconds wait_time, int key)
{
    std::unique_lock<std::mutex> lock(m);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    keys.emplace(now + wait_time, key);
    lock.unlock();
    cv.notify_all();
}

std::vector<int> remove_expired() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<int> expired;
    while (!keys.empty() && keys.top().first <= now) {
        expired.push_back(keys.top().second);
        keys.pop();
    }
    return expired;
}

void timer_thread()
{
    while (!is_cancelled) {
        std::unique_lock<std::mutex> lock(m);
        while (keys.empty() || keys.top().first > std::chrono::system_clock::now()) {
            if (keys.empty())
                cv.wait(lock);
            else
                cv.wait_until(lock, keys.top().first);
        
            if (is_cancelled)
                return;
        }

        std::vector<int> expired = remove_expired();
        lock.unlock();
        std::for_each(expired.begin(), expired.end(), callback);
    }
}
 
int main()
{
    std::thread worker(timer_thread);
    // call some call_later here
    call_later(std::chrono::seconds(2), 2);
    call_later(std::chrono::seconds(1), 4);
    call_later(std::chrono::seconds(3), 6);
    std::this_thread::sleep_for(std::chrono::seconds(5));

    is_cancelled = true;
    cv.notify_all();
    worker.join();
}