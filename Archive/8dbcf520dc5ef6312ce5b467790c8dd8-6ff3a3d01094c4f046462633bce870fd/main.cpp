#include <thread>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <utility>

template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(nullptr),
        thread_(
            [&](Args && ...args) {
                this->obj_ = std::move(std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
                std::cout << *this->obj_ << std::endl;
            },
            std::forward<Args>(args)...
        )
    {
    }
    
    ~Shared()
    {
        thread_.join();
    }
    
    std::unique_ptr<T> obj_;
    std::thread thread_;
};

int
main ()
{
    Shared<std::string> ss (std::string("abcd"));
}
