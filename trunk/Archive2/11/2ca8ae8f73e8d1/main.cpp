#include <boost/asio.hpp>
#include <utility>
#include <mutex>
#include <set>
#include <vector>

template<typename T>
class Singleton
{
public:
    template<typename... As>
    static T& getInstance(As&&... args)
    {
        static T instance{std::forward<As>(args)...};
        return instance;        
    }
    
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&)      = delete;
    
protected:
    Singleton() {}
};

template<typename T>
class Subscriber;

template<typename EvT>
class SubscribtionRegistry : public Singleton<SubscribtionRegistry<EvT>>
{
public:
    inline void registerSubscriber(const Subscriber<EvT>* subscriber)
    {
        std::lock_guard<std::mutex> lock(guard_);
        registry_.insert(subscriber);
    }
    
    inline void unregisterSubscriber(const Subscriber<EvT>* subscriber)
    {
        std::lock_guard<std::mutex> lock(guard_);
        registry_.erase(subscriber);        
    }
    
    inline void dispatchEvent(const EvT& event) const
    {
        guard_.lock();
        decltype(registry_) registry{registry_};
        guard_.unlock();
        for (const auto& subscriber : registry)
        {
            subscriber->processEvent(event);   
        }
    }
    
private:
    std::mutex guard_;
    std::set<const Subscriber<EvT>*> registry_;
};

template<typename EvT>
class Subscriber
{
public:
    Subscriber()
    {
        SubscribtionRegistry<EvT>::getInstnace().registerSubscriber(this); 
    }
    
    ~Subscriber()
    {
        SubscribtionRegistry<EvT>::getInstnace().unregisterSubscriber(this);   
    }
    
    Subscriber(const Subscriber&) = delete;
    Subscriber(Subscriber&&)      = delete;
    
    virtual void processEvent(const EvT& event) const = 0;  
};

template<typename EvT>
inline void dispatchEvent(const EvT& event)
{
    SubscribtionRegistry<EvT>::getInstnace().dispatchEvent(event);
}

template<typename EvT>
inline void postEvent(boost::asio::io_service& ioService, const EvT& event)
{
    ioService.post([&event](){ dispatchEvent(event); });    
}

int main(int argc, char* argv[])
{


    return 0;
}
