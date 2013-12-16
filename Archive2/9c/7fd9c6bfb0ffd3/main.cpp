#include <condition_variable>
#include <iostream>
#include <mutex>
#include <mutex>
#include <thread>
#include <cassert>

class semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public: 
    semaphore(int count_ = 0) : count(count_) { }

    void notify()
    {
        std::unique_lock<std::mutex> lck(mtx);
        ++count;
        cv.notify_one();
    }

    void wait() { return wait([]{}); }  // no-op action

    template <typename F>
    auto wait(F&& func = []{}) -> decltype(std::declval<F>()())
    {
        std::unique_lock<std::mutex> lck(mtx);

        while(count == 0){
            cv.wait(lck);
        }
        count--;

        return func();
    }
};

semaphore sem;

int product = 0;
std::mutex processed_mutex;
std::condition_variable processed_signal;

bool done = false;

void consumer(int check) {
    do {
        bool stop = false;
        int received_product = sem.wait([&stop] { stop = done; return product; });

        if (stop)
            break;

        std::cout << received_product << std::endl;
        assert(++check == received_product);

        std::unique_lock<std::mutex> lock(processed_mutex);
        processed_signal.notify_one();
    } while(true);
}

void producer() {
    std::unique_lock<std::mutex> lock(processed_mutex);
    for(int i = 0; i < 10; ++i) {
        ++product;
        sem.notify();
        processed_signal.wait(lock);
    }
    done = true;
    sem.notify();
}

int main() {
    int t = 1000;
    while(t--) {
        std::thread consumerThread(&consumer, product);
        std::thread producerThread(&producer);
        producerThread.join();
        consumerThread.join();
        done = false;
        std::cout << "process end" << std::endl;
    }
    std::cout << "done" << std::endl;
}
