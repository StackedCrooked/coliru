#include <atomic>
#include <cassert>
#include <future>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "tbb/concurrent_queue.h"

struct Log;

template<typename, typename>
struct LogItem;

void print(const Log&);

template<typename T, typename U>
void print(const LogItem<T, U>& item, char endl = 0);

template<typename T>
void print(const T& t);

// Worker thread which does the actual logging.
struct LoggerThread
{  
    typedef std::function<void()> Task;
    
    LoggerThread() : quit(false), worker([=] { // for now (naked thread is bad)
            thread_started.set_value();
            print("Thread is started!\n");
            Task task;
            while (!quit) {
                queue.pop(task);
                task();
            }
            
            print("Quit flag is set => FLUSH and exit thread.\n");
            
            while (queue.try_pop(task)) task();
            
            print("Logger thread is quitting.\n");
        })
    {
        thread_started.get_future().get();
    }
    
    ~LoggerThread()
    {
        quit = true;
        queue.push([]{}); // unblock the queue
        worker.join();
        print("Logger is destroyed.");
    }
    
    template<typename F>
    void dispatch(F&& f)
    {
        queue.push(Task(f));
    }
    
    std::promise<void> thread_started;
    std::atomic<bool> quit;
    tbb::concurrent_bounded_queue<Task> queue;
    std::thread worker;
};




template<typename Head, typename Tail>
struct LogItem
{   
    template<typename T, typename U>
    LogItem(LoggerThread& logger_thread, T&& t, U&& u) :
        logger_thread(&logger_thread),
        head(std::forward<T>(t)),
        tail(std::forward<U>(u))
    {
    }
    
    LogItem(LogItem<Head, Tail>&&) = default;
    
    ~LogItem()
    {
        if (owns())
        {
            // todo: use raii and find a way to enable move-capture
            auto copy_ptr = new LogItem<Head, Tail>(std::move(*this));
            logger_thread->dispatch([=] {
                std::unique_ptr<LogItem<Head, Tail>> ptr(copy_ptr);
                print(*ptr, '\n');
            });
        }
    }

    template<typename T>
    auto operator<<(T&& t) -> LogItem<LogItem<Head, Tail>, T>
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        return LogItem<LogItem<Head, Tail>, T>(
            *logger_thread,
            std::move(*this),
            std::forward<T>(t)
        );
    }
    
    bool owns() const
    {
        return owns_.owns;
    }
    
    void disown() const
    {
        owns_.disown();
        assert(!owns());
    }
    
    LoggerThread* logger_thread;
    Head head;
    Tail tail;
    
    // Helper which prevents me from having to implement move constructor.
    struct IsOwner
    {
        IsOwner() : owns(true) {}    
        IsOwner(const IsOwner& rhs)  = delete;
        IsOwner& operator=(const IsOwner& rhs) = delete;    
        IsOwner(IsOwner&& rhs) : owns(true) { rhs.owns = false; }
        IsOwner& operator==(IsOwner&& rhs) { this->owns = rhs.owns; rhs.owns = false; return *this; }    
        void disown() const { owns = false; }    
        mutable bool owns;
    };

    IsOwner owns_;
};


template<typename T>
void print(const T& t)
{
    std::cout << t;
}

void print(const Log&)
{
    // dummy
}

template<typename T, typename U>
void print(const LogItem<T, U>& item, char endl)
{
    if (item.owns())
    {
        print(item.head);
        print(item.tail);
        if (endl)
        {
            print(endl);
        }
        item.disown();
    }
}

struct Log
{
    Log(LoggerThread& logger_thread) : logger_thread(&logger_thread) {}
    
    Log(Log&&) = default;
    
    template<typename T>
    auto operator<<(T&& t) -> LogItem<T, Log>
    {
        return LogItem<T, Log>(*logger_thread, std::forward<T>(t), Log(*logger_thread));
    }
    
    LoggerThread* logger_thread;
};


int main()
{
    LoggerThread t;
    Log(t) << 1;    
    Log(t) << 1 << 2;
    Log(t) << 1 << 2 << 3;
    Log(t) << "char array";
    Log(t) << "array-" << std::string("-std::string-") << 123;
    
    // logger goes very quickly out of scope
}

