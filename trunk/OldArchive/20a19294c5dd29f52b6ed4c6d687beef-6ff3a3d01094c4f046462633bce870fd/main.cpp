#include <thread>
#include <boost/optional.hpp>


template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(),
        thread_([=]{ start(std::forward<Args>(args)...); }) // capture by [=] required to ensure lifetime...?
    {
    }
    
    template<typename ...Args>
    void start(Args&& ...args)
    {
        obj_ = T(std::forward<Args>(args)...);
    }
    
    boost::optional<T> obj_;
    std::thread thread_;
};