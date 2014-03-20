#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>


//
// Approach 1: require user to create lock on the outside and use it as an access "key"
// (requires C++11)
// 
struct Value
{    
    Value(int n = 0) : mtx_(), value_(n) {}
    
    // Our lock type (based on std::lock_guard)
    struct ScopedLock : private std::lock_guard<std::mutex>
    {
         ScopedLock(Value& value) : std::lock_guard<std::mutex>(value.mtx_) {}
    };
    
    
    // ScopedLock must be passed to method.
    // This makes it impossible to forget locking.
    int get(ScopedLock&) const
    {
        return value_;
    }
    
    void set(ScopedLock&, int n)
    {
        value_ = n;
    }
    
    void increment(ScopedLock&)
    {
        value_++;
    }
    
    // we can use the lock object to call our own methods
    void increment_until(ScopedLock& lock, int n)
    {
        while (get(lock) < n)
        {
            increment(lock);
        }
    }
    
private:    
    friend struct ScopedLock;
    mutable std::mutex mtx_;
    int value_;
};


void test()
{
    Value value(3);
    
    // using lambda because it provides a scope for our lock and a return value
    auto result = [&]{
        Value::ScopedLock lock(value);
        value.set(lock, 2 * value.get(lock));
        return value.get(lock);
    }();
    
    // IO operation is not under lock
    std::cout << result << std::endl;
}



//
// Approach 2: user accesses the object via lambda (or any function object). lock is created before invoking the lambda
// (requires C++11)
//
struct Alternative
{   
    Alternative(int n = 0) : mtx_(), value_(n) {}
    
    // F must have signature result_type(int&)
    // (result type is deduced from signature and may be void)
    template<typename F>
    auto apply(F&& f) -> decltype(f(std::declval<int&>()))
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return f(value_);
    }
    
    
    // const overload may also be added
    
private:
    mutable std::mutex mtx_;
    int value_;
};


void test_alternative()
{
    Alternative alter(4);
    
    int incremented = alter.apply([](int& n) {
        return ++n;
    });
    
    
    // IO operation is not under lock
    std::cout << incremented << std::endl;
}



int main()
{    
    test();
    test_alternative();
}
