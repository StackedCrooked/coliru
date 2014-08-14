#include <pthread.h>

#include <iostream>
#include <tuple>



class thread
{
    pthread_t _tid;

public:
    thread() :
    _tid(0)
    { }

    template <typename F, typename... Args>
    thread(F f, Args... args)
    {
        auto l = new auto(
            [=] {
                f(args...);
            });
        
        auto te =
            [](void* rp) -> void*
            {
                auto p = reinterpret_cast<decltype(l)>(rp);
                (*p)();
                delete p;
                
                return nullptr;
            };
            
        pthread_create(&_tid, 0, te, l);
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