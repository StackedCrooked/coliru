#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>


std::mutex global_mutex;


#define TRACE() { std::unique_lock<std::mutex> lock(global_mutex); std::cout << std::this_thread::get_id() << "\t" << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl; }


// Encapsulates an object of type T, a queue and a thread. The outside world can
// obtain access to T via callbacks. Callbacks are pushed to the queue from the
// user's thread and popped by the Actor in it's encapsulated thread. The
// callbacks are invoked in this thread as well.
template<typename T>
class Actor
{
public:
    template<typename ...Args>
    Actor(Args && ...args) :
        obj(std::forward<Args>(args)...),
        started(false),
        quit(false),
        consumer_thread(std::bind(&Actor<T>::consume, this)),
        mutex(),
        cond(),
        queue()
    {
        TRACE();
        
        // Wait for our thread to start. 
        
        TRACE();
        std::unique_lock<std::mutex> lock(mutex);
        
        TRACE();
        if (!started)
        {
            TRACE();
            cond.wait_for(lock, std::chrono::milliseconds(500));
        }
        
        TRACE();
    }
    
    ~Actor()
    {
        TRACE();
        {
            std::unique_lock<std::mutex> lock(mutex);
            TRACE();
            quit = true;
            TRACE();
            cond.notify_all();
            TRACE();
        }
        consumer_thread.join();
    }
    
    template<typename Ret>
    std::future<Ret> execute(const std::function<Ret(const T &)> & f)
    {
        TRACE();
        std::unique_lock<std::mutex> lock;
            TRACE();
        auto promisePtr = std::make_shared< std::promise<Ret> >();
            TRACE();
        auto l = [this, f, promisePtr]() { promisePtr->set_value(f(obj)); };
            TRACE();
        Task task(l);
            TRACE();
        queue.push_back(task);
            TRACE();
        auto fut = promisePtr->get_future();
            TRACE();
        return fut;
    } 
    
private:    
    // type erased in order to allow various types of tasks
    typedef std::function<void()> Task;
    
    void consume()
    {
        {
            TRACE();
            started = true;
            TRACE();
            cond.notify_all();
            TRACE();
        }
        
        TRACE();
        while (!quit)
        {
            TRACE();
            std::unique_lock<std::mutex> lock(mutex);
            TRACE();
            cond.wait_for(lock, std::chrono::milliseconds(500));
            TRACE();
            if (!queue.empty())
            {
                TRACE();
                queue.front();
                TRACE();
                queue.pop_front();
                TRACE();
            }
            TRACE();
        }
    }
    
    T obj;    
    std::atomic<bool> started, quit;
    std::thread consumer_thread;
    std::mutex mutex;
    std::condition_variable cond;
    std::deque<Task> queue; // lockless queue would be better
};

struct Car
{
    unsigned age() const
    { 
        TRACE();
        return 2;
        }
};

int main()
{
    TRACE();
    Actor<Car> car;
    TRACE();
    std::future<unsigned> age = car.execute<unsigned>([](const Car & car) -> unsigned { return car.age(); });    
    TRACE();
    age.wait();
    TRACE();
    std::cout << "age: " << age.get() << std::endl;
}
