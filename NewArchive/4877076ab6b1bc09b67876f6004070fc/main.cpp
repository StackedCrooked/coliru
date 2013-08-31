#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <iostream>
#include <thread>
#include <utility>


template<typename T>
struct Actor {
    template<typename ...Args>
    Actor(Args && ...args) : quit_(), obj_(std::forward<Args>(args)...), thread_(std::bind(&Actor<T>::consume, this)) { }

    ~Actor()
    {
        quit_ = true;
        cond_.notify_all();
        thread_.join();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<typename std::result_of<F(T&)>::type>
    {
        auto promisePtr = std::make_shared<std::promise<typename std::result_of<F(T&)>::type>>();
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push_back(std::bind([=]() -> void {
            try {
                promisePtr->set_value(f(obj_));
            } catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
        return promisePtr->get_future();
    }

private:
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;
    
    typedef std::function<void()> Task; // type erased in order to allow various types of tasks

    void consume()
    {
        while (!quit_) {
            Task t; {
                std::unique_lock<std::mutex> lock(mtx_);
                cond_.wait_for(lock, std::chrono::milliseconds(100)); // workaround for unfixed deadlock (yea i suck)
                if (!queue_.empty()) {
                    t = std::move(queue_.front());
                    queue_.pop_front();
                }
            }
            if (t) t();
        }
    }

    std::atomic<bool> quit_;
    std::condition_variable cond_;
    std::mutex mtx_;
    std::deque<Task> queue_; // lockless queue would be better
    T obj_;
    std::thread thread_;
};

struct Car
{
    unsigned age() const { return 777; }
    unsigned weight() const { return 888; }
};

int main()
{
    Actor<Car> a,b,c;    
    auto age_a = a.execute([](Car & c) -> unsigned { return c.age(); });
    auto age_b = b.execute([](Car & c) -> unsigned { return c.age(); });
    auto age_c = c.execute([](Car & c) -> unsigned { return c.age(); });
    std::cout << age_a.get() << std::endl;
    std::cout << age_b.get() << std::endl;
    std::cout << age_c.get() << std::endl;
}
