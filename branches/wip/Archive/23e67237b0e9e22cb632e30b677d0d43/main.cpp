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
        typedef typename std::result_of<F(T&)>::type Ret;
        typedef std::shared_ptr<std::promise<Ret>> SharedPromise;
        
        SharedPromise promisePtr(std::make_shared<std::promise<Ret>>());

        struct functor {
            functor(T & obj, const SharedPromise & promise, F func) : obj_(&obj), promise_(promise), func_(func) { }
            
            void operator()() const { promise_->set_value(func_(*obj_)); }

            T * obj_;
            SharedPromise promise_;
            F func_;
        };

        std::unique_lock<std::mutex> lock(mtx_);
        Task t(std::bind(functor{obj_, promisePtr, f}));
        queue_.push_back(t);
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
    Actor<Car> car;
    std::cout << car.execute([](Car & c) { return c.age(); }).get() << std::endl;
    std::cout << car.execute([](Car & c) { return c.weight(); }).get() << std::endl;
}
