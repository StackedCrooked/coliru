#include <pthread.h>

#include <iostream>
#include <tuple>
#include <memory>
#include <utility>

template<class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>( new T(std::forward<Args>(args)...) );
}



class thread
{
    pthread_t _tid;

public:
    thread() :
    _tid(0)
    { }

    template <typename F, typename... Args>
    thread(F&& f, Args&&... args)
    {
        auto l = [=] {
                f(args...);
            };
        auto dl = make_unique<decltype(l)>(std::move(l));
        
        auto te =
            [](void* rp) -> void*
            {
                auto const p = reinterpret_cast<decltype(l)*>(rp);
                auto mp = decltype(dl) (p);
                (*p)();
                
                return nullptr;
            };
            
        if(0 == pthread_create(&_tid, 0, te, dl.get()))
        {
            dl.release();
        }
    }
    
    void join()
    {
        pthread_join(_tid, nullptr);
    }
};

/** USAGE **/
void
test(int i, char c)
{
    std::cout << "test: ";
    while (i > 0) {
        std::cout << c;
        i--;
    }
    std::cout << std::endl;
}

int main(const int argc, const char** argv)
{
    thread t(test, 6, 'a');
    t.join();
}