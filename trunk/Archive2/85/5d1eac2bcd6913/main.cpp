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
    std::cout << t << ' ' << std::flush;
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


std::atomic<bool> quit(false);


struct Worker
{
    Worker(int cpu, Queue& q1, Queue& q2, Queue& q3, Queue& q4) :
        cpu(cpu),
        q1(q1), q2(q2), q3(q3), q4(q4),
        t([=]{ println("Worker started"); this->run(); })
    {
    }
    
    Worker(Worker&&) = default;
    
    ~Worker()
    {
        std::stringstream ss;
        ss << "Worker destroyed."
            << " cpu=" << cpu
            << "\t\tc1=" << c1
            << "\t\tc2=" << c2
            << "\t\tc3=" << c3
            << "\t\tc4=" << c4
            ;
        println(ss.str());
    }
    
    void run()
    {
        while (!quit)
        {
            if (!process_one())
            {
                //
            }
        }
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
    
    int cpu;
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
        mWorkers.emplace_back(0, q[0], q[1], q[2], q[3]);
        mWorkers.emplace_back(1, q[1], q[0], q[2], q[3]);
        mWorkers.emplace_back(2, q[2], q[3], q[0], q[1]);
        mWorkers.emplace_back(3, q[3], q[2], q[0], q[1]);
    }
    
    ~WorkerPool()
    {
        quit = true;
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

    for (int i = 0; i != 100; ++i)
    {
        workers.schedule([=]{ usleep(10); }, 0);
    }

    for (int i = 0; i != 50; ++i)
    {
        workers.schedule([=]{ usleep(10); }, 1);
    }

    for (int i = 0; i != 40; ++i)
    {
        workers.schedule([=]{ usleep(10); }, 2);
    }

    for (int i = 0; i != 10; ++i)
    {
        workers.schedule([=]{ usleep(10); }, 3);
    }
    
    sleep(1);
    quit = true;
}
