#include <atomic>
#include <cassert>
#include <array>
#include <iostream>
#include <future>
#include <functional>
#include <cstdio>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>
#include <tbb/concurrent_queue.h>


#define TRACE() []{  LOG() << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__; }()


std::mutex m;


struct LogItem
{
    ~LogItem()
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << ss.str() << std::endl;

    }
    std::stringstream ss;
};


#define LOG() LogItem().ss << __FILE__ << ":" << __LINE__ << "   "



using Task = std::function<void()>;


std::atomic<std::uint64_t> gNumExecutors{0};

struct Executor
{
    Executor() : mImpl(std::make_shared<Impl>(this))
    {
    }

    Executor(const Executor&) = default;
    Executor& operator=(const Executor&) = default;

    ~Executor()
    {
        mImpl.reset();
    }

    template<typename F>
    static void Dispatch(F&& f)
    {
        Executor* executor = nullptr;
        GetExecutors().try_pop(executor);

        if (executor)
        {
            executor->mImpl->mTasks.push(f);
        }
        else if (gNumExecutors < hardware_concurrency())
        {
            gNumExecutors++;
            (new Executor)->mImpl->mTasks.push(f);
        }
        else
        {
            f();
        }
    }

private:
    using Executors = tbb::concurrent_bounded_queue<Executor*>;
    
    static unsigned int hardware_concurrency() { return 8; }

    static Executors& GetExecutors()
    {
        static auto fExecutors = []{
            Executors result;
            return result;
        }();
        return fExecutors;
    }

    struct Impl
    {
        Impl(Executor* exec) : mThread([=]{ this->work(exec); })
        {
            LOG() << "Impl: gNumExecutors=" << gNumExecutors;
            mTasks.set_capacity(100);
        }

        ~Impl()
        {
            mTasks.push(Task()); // send stop flag
            mThread.join();
            --gNumExecutors;
            LOG() << "Impl: gNumExecutors=" << gNumExecutors;
        }

        void work(Executor* exec)
        {
            for (;;)
            {
                Task task;
                mTasks.pop(task);

                do
                {
                    // Allow scheduling a new task before we start running the current task.
                    GetExecutors().push(exec);

                    // stop flag
                    if (!task)
                    {
                        LOG() << "Executor received DEATH FLAG!" << std::endl;
                        return;
                    }

                    try
                    {
                        task();
                    }
                    catch (const std::exception& e)
                    {
                        LOG() << "Executor::Impl::work: Caught: " << e.what();
                    }
                }
                while (mTasks.try_pop(task));
            }
        }

        tbb::concurrent_bounded_queue<Task> mTasks;
        std::thread mThread;
    };


    std::shared_ptr<Impl> mImpl;
};


int main()
{
    std::promise<void> keep_alive;

    for (int i = 0; i != 400; ++i)
    {
        Executor::Dispatch([=] { LOG() << "Task " << i << "."; });
    }

    Executor::Dispatch([&] { keep_alive.set_value(); });
    
    
    keep_alive.get_future().get();
}
