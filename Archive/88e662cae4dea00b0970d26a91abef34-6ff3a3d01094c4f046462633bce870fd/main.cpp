#include <thread>


template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(std::forward<Args>(args)...),
        thread_(std::bind(&Shared<T>::consume, this))
    {
    }
    
    T obj_;
    std::thread thread_;
};