#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>


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
        // Wait for our thread to start. 
        
        std::unique_lock<std::mutex> lock(mutex);
        if (!started)
        {
            cond.wait_for(lock, std::chrono::milliseconds(500));
        }
    }
    
    ~Actor()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            quit = true;
            cond.notify_all();
        }
        consumer_thread.join();
    }
    
    template<typename Ret>
    std::future<Ret> execute(const std::function<Ret(const T &)> & f)
    {
        std::unique_lock<std::mutex> lock;
        auto promisePtr = std::make_shared< std::promise<Ret> >();
        auto l = [this, f, promisePtr]() { promisePtr->set_value(f(obj)); };
        Task task(l);
        queue.push_back(task);
        auto fut = promisePtr->get_future();
        return fut;
    } 
    
private:    
    // type erased in order to allow various types of tasks
    typedef std::function<void()> Task;
    
    void consume()
    {
        {
            started = true;
            cond.notify_all();
        }
        
        while (!quit)
        {
            std::unique_lock<std::mutex> lock(mutex);
            cond.wait_for(lock, std::chrono::milliseconds(500));
            if (!queue.empty())
            {
                queue.front()();
                queue.pop_front();
            }
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
    unsigned age() const { return 2; }
};

int main()
{
    Actor<Car> car;
    std::future<unsigned> age = car.execute<unsigned>([](const Car & car) -> unsigned { return car.age(); });    
    age.wait();
    std::cout << "age: " << age.get() << std::endl;
}
