#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include <vector>

namespace
{
    class main_thread
    {
    public:
        static auto instance() -> main_thread&
        {
            static main_thread instance_;
            return instance_;
        }
        auto enque(std::function<void()> func) -> void
        {
            {
                std::lock_guard<std::mutex> lock{ mutex_ };
                queue_.push_back(func);
            }
            condition_.notify_one();
        }
    private:
        main_thread() : continue_{true}
        {
            thread_ = std::thread{ &main_thread::run, this };
        }
        ~main_thread()
        {
            {
                std::lock_guard<std::mutex> lock{ mutex_ };
                continue_ = false;
            }
            condition_.notify_all();
            if (thread_.joinable())
            {
                thread_.join();
            }
        }

        auto run() -> void
        {
            std::unique_lock<std::mutex> lock{ mutex_ };
            while(continue_)
            {
                if(queue_.empty())
                {
                    condition_.wait(lock);
                    continue;
                }

                std::vector<std::function<void()>> queue;
                queue.swap(queue_);
                lock.unlock();
                for (auto &func : queue)
                {
                    func();
                }
                lock.lock();
            }
        }

        std::condition_variable condition_;
        std::mutex mutex_;
        std::vector<std::function<void()>> queue_;
        bool continue_;
        std::thread thread_;
    };
}

auto on_main_thread(std::function<void()> func) -> void
{
    main_thread::instance().enque(std::move(func));
}

template <typename F>
auto on_main_thread_sync(F func) -> void
{
    std::promise<void> promise;

    on_main_thread([&]{
        func();
        promise.set_value();
    });

    return promise.get_future().get();
}

#include <iostream>

int main()
{
    on_main_thread([]{std::cout << "async task" << std::endl;});
    std::this_thread::sleep_for(std::chrono::milliseconds{150});
    on_main_thread_sync([]{std::cout << "sync task" << std::endl;});
}
