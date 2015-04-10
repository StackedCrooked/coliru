#include <thread>
#include <cstddef>
#include <iostream>
#include <vector>
#include <future>

using std::size_t;

// launches n threads all doing task F with an index:
template<class F>
struct mass_thread_pool {
    F f;
    std::vector< std::thread > threads;
    std::condition_variable cv;
    std::mutex m;
    size_t task_id = 0;
    size_t finished_count = 0;
    std::unique_ptr<std::promise<void>> task_done;
    std::atomic<bool> finished;
    
    void task( F f, size_t n, size_t cur_task ) {
        //std::cout << "Thread " << n << " launched" << std::endl;
        do {
            f(n);
            std::unique_lock<std::mutex> lock(m);
            
            if (finished)
                break;
                
            ++finished_count;
            if (finished_count == threads.size())
            {
                //std::cout << "task set finished" << std::endl;
                task_done->set_value();
                finished_count = 0;
            }
            cv.wait(lock,[&]{if (finished) return true; if (cur_task == task_id) return false; cur_task=task_id; return true;});
        } while(!finished);
        //std::cout << finished << std::endl;
        //std::cout << "Thread " << n << " finished" << std::endl;
    }
    
    mass_thread_pool() = delete;
    mass_thread_pool(F fin):f(fin),finished(false) {}
    mass_thread_pool(mass_thread_pool&&)=delete; // address is party of identity
    
    std::future<void> kick( size_t n ) {
        //std::cout << "kicking " << n << " threads off.  Prior count is " << threads.size() << std::endl;
        std::future<void> r;
        {
            std::unique_lock<std::mutex> lock(m);
            ++task_id;
            task_done.reset( new std::promise<void>() );
            finished_count = 0;
            r = task_done->get_future();
            while (threads.size() < n) {
                size_t i = threads.size();
                threads.emplace_back( &mass_thread_pool::task, this, f, i, task_id );
            }
            //std::cout << "count is now " << threads.size() << std::endl;
        }
        cv.notify_all();
        return r;
    }
    ~mass_thread_pool() {
        //std::cout << "destroying thread pool" << std::endl;
        finished = true;
        cv.notify_all();
        for (auto&& t:threads) {
            //std::cout << "joining thread" << std::endl;
            t.join();
        }
        //std::cout << "destroyed thread pool" << std::endl;
    }
};

template<class F>
mass_thread_pool<F> make_pool( F f ) {
    return {std::forward<F>(f)};
}

std::vector<size_t> test() {
    std::vector<size_t> countersA;
    std::vector<size_t> countersB;
    auto&& pool = make_pool( [&](size_t n) {
        countersA[n] = countersB[(n+countersB.size()-1)%countersB.size()]+1;
    });
    countersA.resize(10);
    countersB.resize(10);
    for (auto i = 0; i < 2000; ++i) {
        //std::cout << "Loop " << i << std::endl;
        std::future<void> k = pool.kick(10);
        k.wait();
        countersA.swap(countersB);
        //std::cout << "Loop " << i << " done" << std::endl;
    }
    return countersB;
}

int main() {
    auto counters = test();
    std::cout << counters.size() << ":\n";
    for (size_t i : counters) {
        std::cout << i << '\n';
    }
}