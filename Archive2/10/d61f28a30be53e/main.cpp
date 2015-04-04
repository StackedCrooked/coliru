#include "folly/ThreadCachedArena.h"
#include "folly/MPMCQueue.h"
#include <iostream>


struct TaskQueue
{
    TaskQueue()  :mQueue(1000)
    {
    }

    template<typename F>
    void post(const F& f)
    {
        TaskHolder&& task(new (mArena.allocate(sizeof(f))) F(f));
        mQueue.blockingWrite(std::move(task));
    }

    void poll_one()
    {
        TaskHolder task;
        mQueue.blockingRead(task);
        task.run();
    }

    void poll_all()
    {
        auto n = mQueue.writeCount();
        std::cout << "writeCount=" << n << std::endl;

        while (n--)
        {
            TaskHolder task;
            mQueue.blockingRead(task);
            task.run();
        }

    }

private:
    struct TaskHolder
    {
        TaskHolder() :
            mCallback(),
            mTask()
        {
        }

        template<typename F>
        TaskHolder(F* f) :
            mCallback([](void* ptr) { (*static_cast<F*>(ptr))(); }),
            mTask(f)
        {
        }

        void run() { mCallback(mTask); }

        void (*mCallback)(void*);
        void* mTask;
    };


    static_assert(std::is_trivially_destructible<TaskHolder>::value, "");
    static_assert(std::is_trivially_copyable<TaskHolder>::value, "");


    folly::ThreadCachedArena mArena;
    folly::MPMCQueue<TaskHolder> mQueue;
};


int main()
{
    TaskQueue q;
    q.post([]{ std::cout << "Hello World!" << std::endl; });
    q.post([]{ std::cout << "Hello World!" << std::endl; });
    q.poll_one();
    q.post([]{ std::cout << "Hello World!" << std::endl; });
    q.poll_all();
}
