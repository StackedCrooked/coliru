// http://stackoverflow.com/questions/19593427/actor-calculation-model-using-boostthread

#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/function.hpp>
#include <boost/atomic.hpp>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>

using namespace boost;

struct Actor
{
    typedef function<int()> Job;

    std::queue<Job> d_jobQueue;

    mutex d_jobQueueMutex;
    condition_variable d_hasJob;

    bool d_keepWorkerRunning;
    thread d_worker;

    Actor()
        : d_keepWorkerRunning(true), d_worker(&Actor::workerThread, this)
    {}

    ~Actor() // <------------ PATCH
    {
        execJobSync([this]()->int
        {
            d_keepWorkerRunning = false;
            return 0;
        });
        d_worker.join();
    }

    void execJobAsync(const Job& job)
    {
        mutex::scoped_lock g(d_jobQueueMutex);
        d_jobQueue.push(job);
        d_hasJob.notify_one();
    }

    int execJobSync(const Job& job)
    {
        std::string error;
        promise<int> promise;
        unique_future<int> future = promise.get_future();
        {
            mutex::scoped_lock g(d_jobQueueMutex);
            d_jobQueue.push([&]() -> int
            {
                    int rc = job();    
                    promise.set_value(rc);
                    return 0;
            });
            d_hasJob.notify_one();
        }
        int rc = future.get();
        return rc;
    }

    void workerThread()
    {
        while (d_keepWorkerRunning)
        {
            unique_lock<mutex> g(d_jobQueueMutex);

            while (d_jobQueue.empty()) { d_hasJob.wait(g); }

            Job job = d_jobQueue.front();
            assert(!d_jobQueue.empty());
            d_jobQueue.pop();
            
            g.release(); // <------------ PATCH
            d_jobQueueMutex.unlock();

            job();
        }
    }
};

int main()
{
    using namespace std;
    cout << "start" << endl;
    {
        Actor x;
        for(int i=0; i!=16; ++i)
        {
            cout << i << endl;
            x.execJobSync([=]() -> int { cout << "Sync " << i << endl; return 0; });
            x.execJobAsync([=]() -> int { cout << "Async " << i << endl; return 0; });
        }
    }
    cout << "end" << endl;
}