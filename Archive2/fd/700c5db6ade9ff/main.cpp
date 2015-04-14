#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

static constexpr size_t queue_capacity = 1;

struct Processor {

    Processor(int id) : id_(id) {}

    void work() {
        while (running) {
            int value;
            {   // pop under lock
                std::unique_lock<std::mutex> lk(mx_);
                cv_.wait(lk, [this] { return !running || !queue_.empty(); });

                if (!running)
                    break;

                // invariant: queue cannot be empty here
                value = queue_.front();
                queue_.pop();
                cv_.notify_one();
            }
            std::cout << "work " << id_ << ": " << value << "\n";
        }
    }

    void enqueue(int value) {
        std::unique_lock<std::mutex> lk(mx_);
        cv_.wait(lk, [this] { return !running || queue_.size() < queue_capacity; });
        
        if (running) {
            queue_.push(value);
            cv_.notify_one();
        }
    }

    ~Processor() {
        {
            std::unique_lock<std::mutex> lk(mx_);
            cv_.notify_one();
            running = false;
        }
        if (th_.joinable())
            th_.join();
    }
private:
    bool running = true;
    std::mutex mx_;
    std::condition_variable cv_;
    std::thread th_ {std::bind(&Processor::work, this)};
    int id_;

    std::queue<int> queue_;
};

int main() {
    Processor w1(1), w2(2);

    for (int i = 1; i < 10; ++i)
    {
        w1.enqueue(i*10);
        w2.enqueue(i*20);

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));
}
