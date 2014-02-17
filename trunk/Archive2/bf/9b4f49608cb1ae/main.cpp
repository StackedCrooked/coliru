#include <iostream>
#include <thread>
#include <memory>

class thread_guard
{
    public:
        template<typename... Ts>
            thread_guard(Ts &&... args) noexcept :
            _thread{std::forward<Ts>(args)...}
            { }
        
        thread_guard(thread_guard const &) = delete;
        thread_guard& operator=(thread_guard const &) = delete;

        thread_guard(thread_guard &&other) :
            _thread(std::move(other._thread))
        { }
        
        ~thread_guard() 
        {
            if (_thread.joinable())
                _thread.join();
        }

    private:
        std::thread _thread;
}; 

int main(void) 
{ 
    std::cout << "Before\n";
 
    auto t1 = thread_guard([]() { 
                int i = 10;
                while(i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    std::cout << i-- << std::endl;
                }
            });
    
    std::cout << "After\n";
} 
