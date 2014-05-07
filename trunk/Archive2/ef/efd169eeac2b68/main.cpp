#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <utility>
#include <algorithm>
 
std::mutex m;
std::condition_variable cv;
std::atomic_bool isCancelled(false);
std::vector<std::pair<std::chrono::system_clock::time_point, int>> keys;
std::chrono::system_clock::time_point earliest;

void callback(int key) {
    std::cout<<key<<' '<<std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<std::endl;
}

void set_callback(std::chrono::milliseconds wait_time, int key) {
    std::unique_lock<std::mutex> lock(m);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto expiration_time = now + wait_time;
    keys.emplace_back(expiration_time, key);
    earliest = std::min(earliest, expiration_time);
    lock.unlock();
    cv.notify_all();
}

std::chrono::system_clock::time_point find_next_timeout() {
    return min_element(keys.begin(), keys.end())->first;
}

std::vector<int> remove_expired(std::chrono::system_clock::time_point now) {
    auto has_expired = [&] (const std::pair<std::chrono::system_clock::time_point, int>& item) { return item.first <= now; };
    std::vector<int> expired;
    for (auto &item : keys)
        if (has_expired(item))
            expired.push_back(item.second);
    keys.erase(std::remove_if(keys.begin(), keys.end(), has_expired), keys.end());
    return expired;
}

void timer_thread()
{
    while (!isCancelled) {
        std::unique_lock<std::mutex> lock(m);
        std::chrono::system_clock::time_point now;
        while (keys.empty() || earliest > (now = std::chrono::system_clock::now())) {
            if (keys.empty()) {
                cv.wait(lock);
            } else {
                cv.wait_until(lock, earliest);
            }

            if (isCancelled)
                return;
        }

        std::vector<int> expired = remove_expired(now);
        earliest = find_next_timeout();
        lock.unlock();
        std::for_each(expired.begin(), expired.end(), callback);
    }
}
 
int main()
{
    std::thread worker(timer_thread);
    // call some set_callback here
    set_callback(std::chrono::seconds(1), 2);
    set_callback(std::chrono::seconds(2), 4);
    set_callback(std::chrono::seconds(3), 6);
    std::this_thread::sleep_for(std::chrono::seconds(5));

    isCancelled = true;
    cv.notify_all();
    worker.join();
}