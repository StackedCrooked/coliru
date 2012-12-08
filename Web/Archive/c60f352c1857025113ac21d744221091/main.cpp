#include <functional>
#include <future>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <thread>


#define TRACE() std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY__FUNCTION__ << std::endl


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
        quit(false),
        consumer(std::bind(&Actor<T>::consume, this)),
        mutex(),
        cond(),
        queue()
    {
        TRACE();
    }
    
    ~Actor()
    {
        TRACE();
        std::unique_lock<std::mutex> lock;
        quit = true;
        cond.notify_all();
    }
    
    template<typename Ret>
    std::future<Ret> execute(const std::function<Ret(const T &)> & f)
    {
        TRACE();
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
        TRACE();
        while (!quit)
        {
            std::unique_lock<std::mutex> lock;
            cond.wait(lock);
            if (!queue.empty())
            {
                queue.front();
                queue.pop_front();
            }
        }
    }
    
    T obj;    
    std::atomic<bool> quit;
    std::thread consumer;
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
    std::cout << "age: " << age.get() << std::endl;
}
