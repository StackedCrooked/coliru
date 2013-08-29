#include <chrono>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <thread>


// The Actor class template provides a thread-safety wrapper around an object.
// Access to T can be indirectly achieved by calling the execute(..) method
// with a callback that that takes a T by reference or const-reference.
//
// Callbacks can be posted from any thread and will always be executed on the
// Actor's thread. This removes the need for locking in most situations.
//
// Return values are clumsily encapsulated using std::promise and std::future.
//
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
        queue()
    {
    }
    
    ~Actor()
    {
        {
            quit = true;
        }
        consumer_thread.join();
    }
    
    template<typename Ret>
    std::future<Ret> execute(const std::function<Ret(const T &)> & f)
    {
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
        while (!quit)
        {
            if (!queue.empty())
            {
                queue.front()();
                queue.pop_front();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    
    T obj;    
    std::atomic<bool> started, quit;
    std::thread consumer_thread;
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