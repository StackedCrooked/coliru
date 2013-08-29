#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <iostream>
#include <thread>


// The Actor class template provides a thread-safety wrapper around an object.
// Access to T can be indirectly achieved by calling the execute(..) method
// with a callback that that takes a T by reference or const-reference.
//
// Callbacks can be posted from any thread and will always be executed on the
// Actor's thread. This removes the need for locking in most situations.
//
// Return values are clumsily encapsulated using std::promise and std::future.
//
template<typename T>
class Actor
{
public:
    template<typename ...Args>
    Actor(Args && ...args) :
        quit_(),
        obj_(std::forward<Args>(args)...),
        thread_(std::bind(&Actor<T>::consume, this))
    {
    }

    ~Actor()
    {
        std::lock_guard<std::mutex> lock(mtx_);
        quit_ = true;
        cond_.notify_all();
        thread_.join();
    }

    template<typename Ret>
    std::future<Ret> execute(std::function<Ret(T &)> f)
    {
        typedef std::shared_ptr<std::promise<Ret>> SharedPromise;
        SharedPromise promisePtr(std::make_shared<std::promise<Ret>>());

        struct functor
        {
            functor(T & obj,
                    const SharedPromise & promise,
                    const std::function<Ret(T&)> & func) :
                obj_(&obj),
                promise_(promise),
                func_(func)
            {
            }

            void operator()() const
            {
                promise_->set_value(func_(*obj_));
            }

            T * obj_;
            SharedPromise promise_;
            std::function<Ret(T&)> func_;
        };

        std::lock_guard<std::mutex> lock(mtx_);

        Task t(std::bind(functor{obj_, promisePtr, f}));
        queue_.push_back(t);
        return promisePtr->get_future();
    }

private:
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;

    // type erased in order to allow various types of tasks
    typedef std::function<void()> Task;

    void consume()
    {
        while (!quit_)
        {
            Task t;
            {
                std::lock_guard<std::mutex> lock(mtx_);
                if (!queue_.empty())
                {
                    t = std::move(queue_.front());
                    queue_.pop_front();
                }
            }
            t();
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
    unsigned age() const { return 2; }
};

int main()
{
    Actor<Car> car;
    car.execute<unsigned>([](Car & c) { return c.age(); });
}
