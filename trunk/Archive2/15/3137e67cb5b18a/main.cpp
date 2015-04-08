#include <algorithm>
#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

template<typename T>
class subscription
{
public:
    template<typename F>
    subscription(F&& func) 
      : func_{std::forward<F>(func)}, is_subscribed_{true}
    {}
    
    subscription(subscription&&) = default;

    inline void unsubscribe()
    {
        is_subscribed_.store(false, std::memory_order_relaxed);
    }
    
    inline bool is_subscribed() const
    {
        return is_subscribed_.load(std::memory_order_relaxed);   
    }
    
    inline void notify(const T& value) const
    {
        func_(value);
    }
    
private:
    const std::function<void(const T&)> func_;
    std::atomic<bool> is_subscribed_;    
};

template<typename T>
class observable
{
public:
    observable() = default;
    observable(observable&&) = default;

    template<typename F>
    inline std::shared_ptr<subscription<T>> subscribe(F&& func)
    {
        auto s = std::make_shared<subscription<T>>(std::forward<F>(func));
        std::lock_guard<std::mutex> guard{lock_};
        subscribers_.push_back(s);
        return s;
    }
    
    inline void notify(const T& value) const
    {
        for (const auto& s : subscribers())
        {
            if (s->is_subscribed()) s->notify(value);
        }
    }
    
private:
    inline auto subscribers() const
    {
        std::lock_guard<std::mutex> guard{lock_};
        return decltype(subscribers_){subscribers_};
    }

    mutable std::mutex lock_;
    std::list<std::shared_ptr<subscription<T>>> subscribers_;
};

int main(int argc, char *argv[])
{
    observable<std::string> o;
    o.subscribe([](const auto& v){ std::cout << "subscriber1: " << v << std::endl; });
    o.subscribe([](const auto& v){ std::cout << "subscriber2: " << v << std::endl; });
    auto c = o.subscribe([](const auto& v){ std::cout << "subscriber3: " << v << std::endl; });
    o.notify("hello");
    c->unsubscribe();
    o.notify("world!");



    return 0;   
}
