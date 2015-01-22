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


struct Executor;


using Task = std::function<void(Executor*)>;


std::atomic<std::uint64_t> gNumExecutors{0};

struct Executor
{
    Executor() : mThread([=] { this->work(this); }), mId(++gNumExecutors)
    {
        LOG() << "*** Created Executor " << mId << " ***";
        mTasks.set_capacity(100);
    }

    Executor(const Executor&) = default;
    Executor& operator=(const Executor&) = default;

    ~Executor()
    {
        assert(false); // leak

        mTasks.push(Task()); // send stop flag
        mThread.join();
        LOG() << "Impl: gNumExecutors=" << --gNumExecutors;
    }

    int id() const { return mId; }

    template<typename F>
    static void Dispatch(F&& f)
    {
        Executor* executor = nullptr;
        GetExecutors().try_pop(executor);

        if (executor)
        {
            executor->mTasks.push(f);
        }
        else if (gNumExecutors + 1 < std::thread::hardware_concurrency() || gNumExecutors < 8)  // hack for coliru
        {
            (new Executor)->mTasks.push(f);
        }
        else
        {
            f(nullptr);
        }
    }

private:
    using Executors = tbb::concurrent_queue<Executor*>;

    static Executors& GetExecutors()
    {
        static Executors fExecutors;
        return fExecutors;
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

                if (!task) // called from destructor
                {
                    LOG() << "Executor received DEATH FLAG!" << std::endl;
                    return;
                }

                try
                {
                    task(exec);
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
    int mId;
};


struct Coordinator
{
    Coordinator() :
        mThread([=]
    {
        worker_thread();
    })
    {
    }

    ~Coordinator()
    {
        mTasks.push(Task{});
        mThread.join();
    }

    template<typename F>
    void add_task(F f)
    {
        static_assert(!std::is_same<Task, F>::value, "");
        mTasks.push(f);
    }


private:
    void worker_thread()
    {
        Task task;
        for (;;)
        {
            mTasks.pop(task);
            if (!task)
            {
                LOG() << "Coordinator received DEATH FLAG!" << std::endl;
                return;
            }
            Executor::Dispatch(task);
        }
    }

    tbb::concurrent_bounded_queue<Task> mTasks;
    std::thread mThread;
};


std::atomic<std::uint64_t> tasks{0};



int main()
{
    std::cout << "std::thread::hardware_concurrency()=" << std::thread::hardware_concurrency() << std::endl;
    std::promise<void> keep_alive;


    Coordinator coordinator;

    for (int i = 0; i != 400; ++i)
    {
        coordinator.add_task([=](Executor* exec){ LOG() << "Executor=" << (exec ? exec->id() : 0) << " Task=" << i; });
    }

    coordinator.add_task([&](Executor*){ keep_alive.set_value(); });
    keep_alive.get_future().get();


}
