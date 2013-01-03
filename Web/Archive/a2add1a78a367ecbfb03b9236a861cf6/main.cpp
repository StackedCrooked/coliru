#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <iostream>
#include <thread>


#ifdef ENABLE_TRACE
std::mutex gm;
#define TRACE { \
    std::unique_lock<std::mutex> lock(gm); \
    std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl; \
}
#else
#define TRACE
#endif


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
        quit_ = true;
        cond_.notify_all();
        thread_.join();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<decltype(f(*static_cast<T*>(nullptr)))>
    {
        TRACE
        typedef decltype(f(*static_cast<T*>(nullptr))) Ret;
        typedef std::shared_ptr<std::promise<Ret>> SharedPromise;
        SharedPromise promisePtr(std::make_shared<std::promise<Ret>>());

        struct functor
        {
            functor(T & obj,
                    const SharedPromise & promise,
                    F func) :
                obj_(&obj),
                promise_(promise),
                func_(func)
            {
                TRACE
            }

            void operator()() const
            {
                TRACE
                TRACE
                TRACE
                promise_->set_value(func_(*obj_));
            }

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

    // type erased in order to allow various types of tasks
    typedef std::function<void()> Task;

    void consume()
    {
        while (!quit_)
        {
            Task t;
            {
                TRACE
                std::unique_lock<std::mutex> lock(mtx_);
                cond_.wait_for(lock, std::chrono::milliseconds(100));
                if (!queue_.empty())
                {
                    TRACE
                    t = std::move(queue_.front());
                    queue_.pop_front();
                }
            }
            TRACE
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
    unsigned age() const { return 77777; }
    unsigned weight() const { return 88888; }
};

int main()
{
    Actor<Car> car;
    std::cout << car.execute([](Car & c) { return c.age(); }).get() << std::endl;
    std::cout << car.execute([](Car & c) { return c.weight(); }).get() << std::endl;
}