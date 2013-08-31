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
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        mQuit(),
        mObj(std::forward<Args>(args)...),
        mThread(std::bind(&Shared<T>::consume, this))
    {
    }

    ~Shared()
    {
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mQuit = true;
            mCondition.notify_all();
        }
        mThread.join();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<typename std::result_of<F(T&)>::type>
    {
        auto promisePtr = std::make_shared<std::promise<typename std::result_of<F(T&)>::type>>();
        std::unique_lock<std::mutex> lock(mMutex);
        mQueue.push_back(std::bind([=]() -> void {
            try {
                promisePtr->set_value(f(mObj));
            } catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
        return promisePtr->get_future();
    }

private:
    Shared(const Shared&) = delete;
    Shared& operator=(const Shared&) = delete;
    
    typedef std::function<void()> Task; // type erased in order to allow various types of tasks

    void consume()
    {
        while (!mQuit) {
            Task t; {
                std::unique_lock<std::mutex> lock(mMutex);
                mCondition.wait_for(lock, std::chrono::milliseconds(100)); // workaround for unfixed deadlock (yea i suck)
                if (!mQueue.empty()) {
                    t = std::move(mQueue.front());
                    mQueue.pop_front();
                }
            }
            if (t) t();
        }
    }

    std::atomic<bool> mQuit;
    std::condition_variable mCondition;
    std::mutex mMutex;
    std::deque<Task> mQueue; // lockless queue would be better
    T mObj;
    std::thread mThread;
};

struct Car
{
    unsigned age() const { return 777; }
    unsigned weight() const { return 888; }
};

int main()
{
    Shared<Car> a,b,c;    
    auto age_a = a.execute([](Car & c) -> unsigned { return c.age(); });
    auto age_b = b.execute([](Car & c) -> unsigned { return c.age(); });
    auto age_c = c.execute([](Car & c) -> unsigned { return c.age(); });
    std::cout << age_a.get() << std::endl;
    std::cout << age_b.get() << std::endl;
    std::cout << age_c.get() << std::endl;
}
