#include <iostream>
#include <thread>
#include <memory>

class thread_guard
{
    public:
        thread_guard() noexcept = default;
        thread_guard(std::thread&& thread) noexcept;
        thread_guard(thread_guard const &) = delete;
        thread_guard(thread_guard &&) = delete;
        thread_guard& operator=(thread_guard const &) = delete;
        
        ~thread_guard();

        static std::unique_ptr<thread_guard> make_tg(std::function<void()> fn);
                
    private:
        std::thread _thread;
}; 

thread_guard::thread_guard(std::thread&& thread) noexcept :
    _thread(std::move(thread))
{ }

thread_guard::~thread_guard()
{   
    if (_thread.joinable())
        _thread.join();
}

std::unique_ptr<thread_guard> thread_guard::make_tg(std::function<void()> fn)
{
    auto tg = std::unique_ptr<thread_guard>(new thread_guard(std::thread(fn)));
    return std::move(tg);
}

int main(void) 
{ 
    std::cout << "Before\n";
    auto tt = thread_guard::make_tg([]() { 
                int i=10;
                while(i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    std::cout << i-- << std::endl;
                }
            } );

    std::cout << "After\n";
} 
