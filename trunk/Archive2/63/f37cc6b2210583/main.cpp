#include <tbb/concurrent_queue.h>
#include <functional>
#include <atomic>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
#include <stdio.h>


namespace {
    
std::mutex print_mutex;

typedef std::lock_guard<std::mutex> Lock;


template<typename T>
void print(T&& t)
{
    Lock lock(print_mutex);
    std::cout << t << std::flush;
}


template<typename T>
void println(T&& t)
{
    Lock lock(print_mutex);
    std::cout << std::dec << t << std::endl;
}

}


struct Task
{
    typedef std::function<void()> Function;
    
    Task() {}
    
    template<typename F>
    Task(F&& f, int cpu) : f(std::forward<F>(f)), cpu(cpu) {}
    
    void operator()() const
    {
        f();
    }
    Function f;
    int cpu;
};

typedef tbb::concurrent_queue<Task> Queue;


struct Worker
{
    Worker(Queue& q1, Queue& q2, Queue& q3, Queue& q4) :
        quit(),
        q1(q1), q2(q2), q3(q3), q4(q4),
        t([=]{ this->run(); })
    {
    }
    
    Worker(Worker&&) = default;
    
    ~Worker()
    {
        std::stringstream ss;
        ss << "Worker destroyed. Stats:"
            << " c1=" << c1
            << " c2=" << c2
            << " c3=" << c3
            << " c4=" << c4
            ;
        println(ss.str());
    }
    
    void run()
    {
        while (!quit)
        {
            if (!process_one())
            {
                sched_yield();
            }
        }
    }
    
    void stop()
    {
        quit = true;
    }
    
    void join()
    {
        t.join();
    }
    
    bool process_one()
    {
        Task task;
        if (q1.try_pop(task))
        {
            c1++;
            task();  
            return true;
        }
            
        if (q2.try_pop(task))
        {
            c2++;
            task();   
            return true;
        }
        
        if (q3.try_pop(task))
        {
            c3++;
            task();   
            return true;
        }
        
        if (q4.try_pop(task))
        {
            c4++;
            task();    
            return true;
        }
        
        return false;
    }
    
    bool quit;
    Queue& q1; // L1 hit
    Queue& q2; // L1 miss, L2 hit
    Queue& q3; // L2 miss, L3 hit
    Queue& q4; // L3 miss, fetch from RAM
    
    uint32_t c1, c2, c3, c4;
    std::thread t;
};
        

struct WorkerPool
{
    WorkerPool() : mWorkers()
    {
        mWorkers.reserve(4);
        mWorkers.emplace_back(q[0], q[1], q[2], q[3]);
        mWorkers.emplace_back(q[1], q[2], q[2], q[3]);
        mWorkers.emplace_back(q[2], q[3], q[0], q[1]);
        mWorkers.emplace_back(q[3], q[2], q[0], q[1]);
    }
    
    ~WorkerPool()
    {
        println("WorkerPool cleanup: stopping workers...");
        for (auto&& w : mWorkers) w.stop();
        println("WorkerPool cleanup: joining workers...");
        for (auto&& w : mWorkers) w.join();
        println("WorkerPool cleanup: done");
    }
    
    
    
    template<typename F>
    void schedule(F&& f, int cpu)
    {
        q[cpu].push(Task(std::forward<F>(f), cpu));
    }
    
    std::vector<Worker> mWorkers;
    Queue q[4];
};


int main()
{
    WorkerPool workers;
    workers.schedule([]{ println(__LINE__); }, 0);
    workers.schedule([]{ println(__LINE__); }, 1);
    workers.schedule([]{ println(__LINE__); }, 2);
    workers.schedule([]{ println(__LINE__); }, 3);
    
    workers.schedule([]{ println(__LINE__); }, 0);
    workers.schedule([]{ println(__LINE__); }, 1);
    workers.schedule([]{ println(__LINE__); }, 2);
    workers.schedule([]{ println(__LINE__); }, 3);
    
    workers.schedule([]{ println(__LINE__); }, 0);
    workers.schedule([]{ println(__LINE__); }, 1);
    workers.schedule([]{ println(__LINE__); }, 2);
    workers.schedule([]{ println(__LINE__); }, 3);
    
    workers.schedule([]{ println(__LINE__); }, 0);
    workers.schedule([]{ println(__LINE__); }, 1);
    workers.schedule([]{ println(__LINE__); }, 2);
    workers.schedule([]{ println(__LINE__); }, 3);
    
    sleep(1);
}
