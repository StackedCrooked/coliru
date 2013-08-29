#include <thread>


template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(nullptr),//(std::forward<Args>(args)...),
        thread_(//std::bind(&Shared<T>::consume, this)
            std::move ([&](Args && ...args) {
                this->obj = new T(std::forward<Args>(args)...);
            }),
            std::forward<Args>(args)...
        )
    {
    }
    
    T * obj_;
    std::thread thread_;
};