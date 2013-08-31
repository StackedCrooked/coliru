#include <atomic>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template<typename T> class Locker;

template<typename T>
class LockObject {
public:
    Locker<T> lock() { return Locker<T>(*this); }
    
private:
    friend class Locker<T>;
    std::mutex mtx_;
    T obj_;
};

template<typename T>
class Locker {
public:
    // locks the mutex
    Locker(LockObject<T> & lockObject) : lock_(lockObject.mtx_), obj_(lockObject.obj_)  { }    
    const T & get() const { return obj_; }    
    T & get() { return obj_; }
    
private:
    std::unique_lock<std::mutex> lock_;
    T & obj_;
};

int main()
{
    typedef std::queue<char> Queue;
    LockObject<Queue> shared_queue;
    std::atomic<bool> quit;
    
    // producer adds items to the queue
    std::thread producer([&shared_queue, &quit]()
    {
        while (!quit)
        {
            Locker<Queue> lock = shared_queue.lock(); // locks the mutex        
            Queue & queue = lock.get();
            for (char c = ' '; c <= '~'; ++c)
            {
                queue.push(c);
            }
        }
    });
    
    // consumer thread removes items from the queue
    std::thread consumer([&shared_queue, &quit]()
    {
        while (!quit)
        {
            std::string current;
            {
                Locker<Queue> lock = shared_queue.lock(); // locks the mutex        
                Queue & queue = lock.get(); 
                if (queue.empty()) return;
                while (!queue.empty())
                {
                    current.push_back(std::move(queue.front()));
                    queue.pop();
                }
            }
            std::cout << current << '\n';
            current.clear();
        }
    });    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    quit = true;
    producer.join();
    consumer.join();
}
