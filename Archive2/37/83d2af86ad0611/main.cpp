#include <thread>
#include <iostream>

class thread_guard{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t {t_} {}
    ~thread_guard()
    {
        if(t.joinable())
            t.join();
        std::cout << "~thread_guard running" << std::endl;
    }
};

int main()
{
    std::thread t;
    thread_guard tg(t);
}
