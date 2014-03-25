#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>
#include <thread>
#include <tbb/concurrent_queue.h>


std::atomic<bool> atomic_quit_flag(false);
std::atomic<long> atomic_global_sum(0);


// Batch size is defined at compile-time.
// Larger batch sizes require less synchronization but copy is more expensive.
struct Batch
{
    Batch() : data_(), size_() {}

    void push_back(long n)
    {
        data_[size_++] = n;
    }

    long sum() const
    {
        long result = 0;
        for (auto n : *this) { result += n; }
        return result;
    }

    const long* begin() const { return data_.begin(); }
    const long* end() const { return begin() + size(); }
    bool empty() const { return size() == 0; }

    long size() const { return size_; }
    long capacity() const { return data_.size(); }

    std::array<long, BATCH_SIZE> data_;
    int size_;
};

tbb::concurrent_queue<Batch> q;

int main(int argc, char** argv)
{
    std::thread consumer([]{
        while (!atomic_quit_flag) { // atomic check
            Batch batch;
            if (q.try_pop(batch)) { // concurrent pop
                atomic_global_sum += batch.sum(); // atomic increment
            }
        }
    });

    std::thread producer([]{
        while (!atomic_quit_flag) { // atomic read
            Batch batch;
            while (batch.size() != batch.capacity()) {
                batch.push_back(1);
            }
            q.push(batch); // concurrent push
        }
    });
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    atomic_quit_flag = true;
    
    producer.join();
    consumer.join();
    
    std::cout << atomic_global_sum << std::endl;
}

