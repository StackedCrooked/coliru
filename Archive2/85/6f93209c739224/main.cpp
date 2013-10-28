// http://stackoverflow.com/questions/19593427/actor-calculation-model-using-boostthread
// g++ -std=c++11 -O3 -mtune=native -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread -lboost_chrono && ./a.out

#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/function.hpp>
#include <boost/atomic.hpp>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>

using namespace boost;

template<typename T>
class concurrent_queue
{
    std::queue<T> q;
    mutable mutex m;
    mutable condition_variable c;

    void dequeue(T &result)
    {
        result = q.front();
        q.pop();
    }
public:
    void push(const T &t)
    {
        lock_guard<mutex> l(m);
        q.push(t);
        c.notify_one();
    }
    void pop(T &result)
    {
        unique_lock<mutex> u(m);
        c.wait(u, [this]{ return !q.empty(); } );
        dequeue(result);
    }
    bool try_pop(T &result)
    {
        mutex::scoped_lock u(m);
        if(q.empty()) return false;

        dequeue(result);
        return true;
    }
    template<typename Duration>
    bool try_pop(T &result, Duration timeout)
    {
        unique_lock<mutex> u(m);
        c.wait_for(u, timeout, [this]{ return !q.empty(); } );

        if(q.empty()) return false;

        dequeue(result);
        return true;
    }
};

struct Actor
{
    typedef function<int()> Job;

    concurrent_queue<Job> d_jobQueue;

    bool d_keepWorkerRunning;
    thread d_worker;

    Actor()
        : d_keepWorkerRunning(true), d_worker(&Actor::workerThread, this)
    {}

    ~Actor()
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
        d_jobQueue.push(job);
    }

    int execJobSync(const Job& job)
    {
        std::string error;
        promise<int> promise;
        unique_future<int> future = promise.get_future();

        d_jobQueue.push([&]() -> int
        {
                int rc = job();    
                promise.set_value(rc);
                return 0;
        });

        int rc = future.get();
        return rc;
    }

    void workerThread()
    {
        Job job;
        while (d_keepWorkerRunning)
        {
            d_jobQueue.pop(job);
            job();
        }
    }
};

typedef int EventImpl;
typedef concurrent_queue<EventImpl *> EventQueueImpl;

int main()
{
    using namespace std;
    cout << "start" << endl;
    {
        Actor x;
        EventQueueImpl eventQueue;
        for(int i=0; i!=16; ++i)
        {
            cout << i << endl;
            x.execJobSync([=]() -> int { cout << "Sync " << i << endl; return 0; });
            x.execJobAsync([=]() -> int { cout << "Async " << i << endl; return 0; });
        }
        EventImpl z;
        x.execJobSync([&]() -> int {cout << "gen event" << endl; eventQueue.push(&z); return 0;});

        EventImpl *result = nullptr;
        eventQueue.try_pop(result, chrono::milliseconds(10*1000));
        cout << (&z == result) << endl;
    }
    cout << "end" << endl;
}