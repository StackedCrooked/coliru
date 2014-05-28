#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

class ThreadPool {
    std::mutex mtx;
    std::queue<std::function<void()>> tasks;
    std::condition_variable wait_for_tasks;
    std::vector<std::thread> threads;
    bool stop = false;

    void worker();

public:
    ThreadPool() = default;
    ThreadPool(unsigned n) {
        spawnWorkers(n);
    }
    ~ThreadPool() {
        waitFinished();
    }
    void waitFinished();
    void enqueue(std::function<void()> task);
    void spawnWorkers(unsigned n);
};

// called in main after all tasks are enqueued to 
// std::deque<std::function<void()>> tasks
void ThreadPool::waitFinished()
{
    {
        std::lock_guard<std::mutex> _(mtx);
        stop = true;
    }
    // Wake up any sleeping threads so they see we are finished.
    wait_for_tasks.notify_all();

    for (auto&& t : threads) {
        t.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> _(mtx);
        tasks.emplace(std::move(task));
    }
    wait_for_tasks.notify_one();
}

void ThreadPool::worker() {
    std::unique_lock<std::mutex> lock(mtx);
    for (;;) {
        while (!tasks.empty()) {
            auto task = std::move(tasks.front());
            tasks.pop();

            lock.unlock();
            task();
            lock.lock();
        }
        
        if (stop)
            break;
            
        wait_for_tasks.wait(lock);
    }
}

void ThreadPool::spawnWorkers(unsigned n) {
    std::lock_guard<std::mutex> _(mtx);
    threads.reserve(threads.size() + n);
    for (unsigned i = 0; i < n; ++i) {
        threads.emplace_back(&ThreadPool::worker, this);
    }
}

#include <chrono>
#include <iostream>
#include <random>

void job(unsigned i, unsigned wait) {
    std::this_thread::sleep_for(std::chrono::milliseconds{wait});
    std::cout << "Job " << i << '\n';
}

int main() {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<unsigned> dist(100u, 500u);

    ThreadPool pool(4);

    for (unsigned i = 0; i < 8; ++i) {
        auto wait = dist(engine);
        pool.enqueue([=]{ job(i, wait); });
    }
}
